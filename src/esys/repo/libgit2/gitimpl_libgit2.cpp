/*!
 * \file esys/repo/libgit2/gitimpl_libgit2.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/libgit2/gitimpl.h"
#include "esys/repo/libgit2/guard.h"

#include <git2.h>
#include <libssh2.h>

#include <cstring>
#include <sstream>

namespace esys
{

namespace repo
{

namespace libgit2
{

std::unique_ptr<LibGit2> GitImpl::s_libgt2 = nullptr;

GitImpl::GitImpl(Git *self)
    : m_self(self)
{
    if (s_libgt2 == nullptr) s_libgt2 = std::make_unique<LibGit2>();
}

GitImpl::~GitImpl()
{
    if (m_repo != nullptr) close();
}

int GitImpl::open(const std::string &folder)
{
    int result = git_repository_open(&m_repo, folder.c_str());
    if (result < 0) return check_error(result, "open git repo " + folder);

    return 0;
}

bool GitImpl::is_open()
{
    return (m_repo != nullptr);
}

int GitImpl::close()
{
    if (m_repo == nullptr) return -1;

    git_repository_free(m_repo);

    m_repo = nullptr;

    return 0;
}

int GitImpl::get_remotes(std::vector<git::Remote> &remotes)
{
    if (m_repo == nullptr) return -1;

    git_strarray data;

    int result = git_remote_list(&data, m_repo);
    if (result < 0) return -1;

    char **p = data.strings;

    if (data.count == 0) return 0;
    if (p == nullptr) return -1;

    for (auto idx = 0; idx < data.count; ++idx)
    {
        char *name = *p;
        if (name == nullptr) return -1;

        git::Remote remote;

        remote.set_name(name);

        remotes.push_back(remote);
        p += strlen(*p);
    }

    for (auto &remote_item : remotes)
    {
        Guard<git_remote> remote; // This will automically release the git_remote

        const git_remote_head **refs;
        size_t refs_len, i;
        git_remote_callbacks callbacks = GIT_REMOTE_CALLBACKS_INIT;

        // Find the remote by name
        result = git_remote_lookup(remote.get_p(), m_repo, remote_item.get_name().c_str());
        if (result < 0) return check_error(result, "");

        const char *url = git_remote_url(remote.get());
        remote_item.set_url(url);

        /*result = git_remote_ls(&refs, &refs_len, remote.get());
        if (result < 0) return check_error(result, ""); */
    }

    return 0;
}

int GitImpl::get_branches(std::vector<git::Branch> &branches, git::BranchType branch_type)
{
    if (m_repo == nullptr) return -1;

    Guard<git_branch_iterator> branch_it;
    git_branch_t list_flags;

    switch (branch_type)
    {
        case git::BranchType::ALL: list_flags = GIT_BRANCH_ALL; break;
        case git::BranchType::LOCAL: list_flags = GIT_BRANCH_LOCAL; break;
        case git::BranchType::REMOTE: list_flags = GIT_BRANCH_REMOTE; break;
        default: list_flags = GIT_BRANCH_LOCAL;
    }

    int result = git_branch_iterator_new(branch_it.get_p(), m_repo, list_flags);
    if (result < 0) return check_error(result);

    while (true)
    {
        Guard<git_reference> ref;
        git_branch_t git_branch_type;

        result = git_branch_next(ref.get_p(), &git_branch_type, branch_it.get());
        if (result == GIT_ITEROVER) return 0;
        if (result < 0) return check_error(result);

        git::Branch branch;
        const char *branch_name;
        result = git_branch_name(&branch_name, ref.get());
        if (result < 0) return check_error(result);

        branch.set_name(branch_name);

        switch (git_branch_type)
        {
            case GIT_BRANCH_ALL: branch_type = git::BranchType::ALL; break;
            case GIT_BRANCH_LOCAL: branch_type = git::BranchType::LOCAL; break;
            case GIT_BRANCH_REMOTE: branch_type = git::BranchType::REMOTE; break;
            default: branch_type = git::BranchType::NOT_SET;
        }

        branch.set_type(branch_type);

        result = git_branch_is_head(ref.get());
        if (result == 1) branch.set_is_head(true);

        branches.push_back(branch);
    }

    return 0;
}

int GitImpl::clone(const std::string &url, const std::string &path)
{
    int result = 0;

    if (url.find("https:") == 0)
        result = git_clone(&m_repo, url.c_str(), path.c_str(), nullptr);
    else if ((url.find("ssh:") == 0))
    {
        git_clone_options opts = GIT_CLONE_OPTIONS_INIT;
        // opts.fetch_opts.callbacks.connect = &Remote::Callbacks::connect;
        // opts.fetch_opts.callbacks.disconnect = &Remote::Callbacks::disconnect;
        // opts.fetch_opts.callbacks.sideband_progress = &Remote::Callbacks::sideband;
        opts.fetch_opts.callbacks.credentials = &GitImpl::libgit2_credentials;
        // opts.fetch_opts.callbacks.certificate_check = &Remote::Callbacks::certificate;
        // opts.fetch_opts.callbacks.transfer_progress = &Remote::Callbacks::transfer;
        // opts.fetch_opts.callbacks.update_tips = &Remote::Callbacks::update;
        // opts.fetch_opts.callbacks.resolve_url = &Remote::Callbacks::url;
        opts.fetch_opts.callbacks.payload = this;
        // opts.bare = bare;
        // git_credential_ssh_key_from_agent(m_credential.get_p(), name);

        result = git_clone(&m_repo, url.c_str(), path.c_str(), &opts);
    }
    else
        result = -1;

    return result;
}

int GitImpl::checkout(const std::string &branch, bool force)
{
    Guard<git_object> treeish;

    int result = git_revparse_single(treeish.get_p(), m_repo, branch.c_str());
    if (result < 0) return result;

    git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
    if (force)
        opts.checkout_strategy = GIT_CHECKOUT_FORCE;
    else
        opts.checkout_strategy = GIT_CHECKOUT_SAFE;

    result = git_checkout_tree(m_repo, treeish.get(), &opts);
    return result;
}

int GitImpl::get_last_commit(git::Commit &commit)
{
    if (m_repo == nullptr) return -1;

    int result;
    Guard<git_commit> g_commit;
    git_oid oid_last_commit;

    // resolve HEAD into a SHA1
    result = git_reference_name_to_id(&oid_last_commit, m_repo, "HEAD");
    if (result < 0) return result;

    // get the actual commit structure
    result = git_commit_lookup(g_commit.get_p(), m_repo, &oid_last_commit);
    if (result < 0) return result;

    std::string hash;
    result = convert_bin_hex(oid_last_commit, hash);
    if (result == 0) commit.set_hash(hash);

    return 0;
}

int GitImpl::is_dirty(bool &dirty)
{
    if (m_repo == nullptr) return -1;

    Guard<git_status_list> status;
    git_status_options statusopt = GIT_STATUS_OPTIONS_INIT;

    statusopt.show = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
    statusopt.flags = GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX | GIT_STATUS_OPT_SORT_CASE_SENSITIVELY;

    int result = git_status_list_new(status.get_p(), m_repo, &statusopt);
    if (result < 0) return result;

    std::size_t count = git_status_list_entrycount(status.get());
    dirty = (count != 0);
    return 0;
}

int GitImpl::check_error(int result, const std::string &action)
{
    const git_error *error = git_error_last();
    if (!result) return 0;

    std::ostringstream oss;
    oss << "ERROR " << result << " : " << action << " - ";
    oss << ((error && error->message) ? error->message : "???") << std::endl;

    self()->error(oss.str());
    return result;
}

Git *GitImpl::self() const
{
    return m_self;
}

int GitImpl::libgit2_credentials(git_credential **out, const char *url, const char *name, unsigned int types,
                                 void *payload)
{
    const git_error *error = git_error_last();
    if (error && error->klass == GIT_ERROR_SSH) return -1;

    GitImpl *self = reinterpret_cast<GitImpl *>(payload);

    if (self->is_ssh_agent_running()) return git_credential_ssh_key_from_agent(out, name);

    return -1;
}

bool GitImpl::is_ssh_agent_running()
{
    LIBSSH2_SESSION *session = libssh2_session_init();
    LIBSSH2_AGENT *agent = libssh2_agent_init(session);

    int error = libssh2_agent_connect(agent);
    if (error != LIBSSH2_ERROR_NONE)
    {
        char *msg;
        libssh2_session_last_error(session, &msg, nullptr, 0);

        std::ostringstream oss;
        oss << "agent error (" << error << ") : " << msg << std::endl;
        self()->error(oss.str());
    }
    else
        self()->info("SSH agent detected");

    libssh2_agent_disconnect(agent);
    libssh2_agent_free(agent);
    libssh2_session_free(session);

    return (error == LIBSSH2_ERROR_NONE);
}

int GitImpl::convert_bin_hex(const git_oid &oid, std::string &hex_str)
{
    char temp[GIT_OID_HEXSZ + 1];

    int result = git_oid_fmt(temp, &oid);
    if (result < 0) return result;
    temp[GIT_OID_HEXSZ] = 0;
    hex_str = std::string(temp);
    return 0;
}

const std::string &GitImpl::get_version()
{
    return s_get_version();
}

const std::string &GitImpl::get_lib_name()
{
    return s_get_lib_name();
}

const std::string &GitImpl::s_get_version()
{
    static std::string s_version = LIBGIT2_VERSION;
    return s_version;
}

const std::string &GitImpl::s_get_lib_name()
{
    static std::string s_lib_name = "libgit2";
    return s_lib_name;
}

const std::string &GitImpl::s_get_ssh_version()
{
    static std::string s_version = LIBSSH2_VERSION;
    return s_version;
}

const std::string &GitImpl::s_get_ssh_lib_name()
{
    static std::string s_lib_name = "libssh2";
    return s_lib_name;
}

} // namespace libgit2

} // namespace repo

} // namespace esys
