/*!
 * \file esys/repo/libgit2/gitimpl_libgit2.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2022 Michel Gillet
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
#include "esys/repo/libgit2/guards.h"
#include "esys/repo/git/updatetip.h"
#include "esys/repo/libssh2/ssh.h"

#include <git2.h>
#include <libssh2.h>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include <cstring>
#include <sstream>
#include <cassert>
#include <algorithm>

#include <iostream>

namespace esys::repo::libgit2
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
    self()->open_time();

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

    self()->close_time();

    return 0;
}

int GitImpl::get_remotes(std::vector<git::Remote> &remotes)
{
    if (m_repo == nullptr) return -1;

    self()->cmd_start();

    GuardS<git_strarray> data;

    int result = git_remote_list(data.get(), m_repo);
    if (result < 0) return check_error(result);

    char **p = data.get()->strings;

    if (data.get()->count == 0) return check_error(0);
    if (p == nullptr) return check_error(-1, "Not data");

    for (auto idx = 0; idx < data.get()->count; ++idx)
    {
        char *name = *p;
        if (name == nullptr) return check_error(-1, "Not name");

        git::Remote remote;

        remote.set_name(name);

        remotes.push_back(remote);
        p += strlen(*p);
    }

    for (auto &remote_item : remotes)
    {
        Guard<git_remote> remote; // This will automically release the git_remote

        const git_remote_head **refs = nullptr;
        size_t refs_len = 0;
        size_t i = 0;
        git_remote_callbacks callbacks = GIT_REMOTE_CALLBACKS_INIT;

        // Find the remote by name
        result = git_remote_lookup(remote.get_p(), m_repo, remote_item.get_name().c_str());
        if (result < 0) return check_error(result, "");

        const char *url = git_remote_url(remote.get());
        remote_item.set_url(url);

        /*result = git_remote_ls(&refs, &refs_len, remote.get());
        if (result < 0) return check_error(result, ""); */
    }

    return check_error(0);
}

int GitImpl::get_branches(git::Branches &branches, git::BranchType branch_type)
{
    if (m_repo == nullptr) return -1;

    self()->cmd_start();

    Guard<git_branch_iterator> branch_it;
    git_branch_t list_flags = GIT_BRANCH_ALL;

    convert(branch_type, list_flags);

    int result = git_branch_iterator_new(branch_it.get_p(), m_repo, list_flags);
    if (result < 0) return check_error(result);

    while (true)
    {
        Guard<git_reference> ref;
        git_branch_t git_branch_type = GIT_BRANCH_ALL;

        result = git_branch_next(ref.get_p(), &git_branch_type, branch_it.get());
        if (result == GIT_ITEROVER) return check_error(0);
        if (result < 0) return check_error(result);

        std::shared_ptr<git::Branch> branch = std::make_shared<git::Branch>();
        const char *branch_name = nullptr;
        result = git_branch_name(&branch_name, ref.get());
        if (result < 0) return check_error(result);

        std::string ref_name = git_reference_name(ref.get());

        branch->set_name(branch_name);
        branch->set_ref_name(ref_name);

        switch (git_branch_type)
        {
            case GIT_BRANCH_ALL: branch_type = git::BranchType::ALL; break;
            case GIT_BRANCH_LOCAL: branch_type = git::BranchType::LOCAL; break;
            case GIT_BRANCH_REMOTE: branch_type = git::BranchType::REMOTE; break;
            default: branch_type = git::BranchType::NOT_SET;
        }

        branch->set_type(branch_type);

        result = git_branch_is_head(ref.get());
        if (result == 1) branch->set_is_head(true);

        if (branch_type == git::BranchType::LOCAL)
        {
            git_buf buf_out = {nullptr};
            result = git_branch_upstream_remote(&buf_out, m_repo, ref_name.c_str());
            if (result == 0)
            {
                std::string remote_name(buf_out.ptr, buf_out.ptr + buf_out.size);
                branch->set_remote_name(remote_name);
                git_buf_dispose(&buf_out);
            }
            result = git_branch_upstream_name(&buf_out, m_repo, ref_name.c_str());
            if (result == 0)
            {
                std::string remote_branch(buf_out.ptr, buf_out.ptr + buf_out.size);
                branch->set_remote_branch(remote_branch);
                git_buf_dispose(&buf_out);
            }
        }
        else
            check_error(result, "");
        branches.add(branch);
    }
    return check_error(0);
}

bool GitImpl::has_branch(const std::string &name, git::BranchType branch_type)
{
    Guard<git_reference> ref;
    git_branch_t git_branch_type = GIT_BRANCH_ALL;
    Guard<git_annotated_commit> annotated_commit;
    // Guard<git_reference> branch_ref;
    Guard<git_reference> input_branch_ref;
    std::string new_ref = name;

    int result = resolve_ref(input_branch_ref.get_p(), annotated_commit.get_p(), name);
    if (result < 0)
    {
        self()->debug(0, "branch not found : " + name);
        // In the case where the content of branch doesn't have the full qualifier,
        // try to to guess

        result = find_ref(input_branch_ref.get_p(), annotated_commit.get_p(), name, new_ref);
        if (result < 0) return false;
    }

    return true;
}

int GitImpl::get_hash(const std::string &revision, std::string &hash, git::BranchType branch_type)
{
    Guard<git_annotated_commit> annotated_commit;
    Guard<git_reference> revision_ref;
    std::string new_ref = revision;

    int result = resolve_ref(revision_ref.get_p(), annotated_commit.get_p(), revision);
    if (result < 0)
    {
        self()->debug(0, "revision not found : " + revision);
        // In the case where the content of branch doesn't have the full qualifier,
        // try to to guess

        result = find_ref(revision_ref.get_p(), annotated_commit.get_p(), revision, new_ref);
        if (result < 0) return check_error(result);
    }

    const git_oid *oid = git_annotated_commit_id(annotated_commit.get());
    if (oid == nullptr) return -1;

    result = convert_bin_hex(*oid, hash);
    if (result < 0) return -2;
    return 0;
}

int GitImpl::treeish_to_tree(Guard<git_tree> &tree, git_repository *repo, const char *treeish)
{
    Guard<git_object> obj;

    int result = git_revparse_single(obj.get_p(), repo, treeish);
    if (result < 0) return -1;

    result = git_object_peel((git_object **)tree.get_p(), obj.get(), GIT_OBJECT_TREE);

    if (result < 0) return -1;
    return 0;
}

int GitImpl::walk_commits(std::shared_ptr<git::WalkCommit> walk_commit)
{
    if (m_repo == nullptr) return -1;
    if (walk_commit == nullptr) return -1;

    git::CommitHash hash;
    int result = get_last_commit(hash);
    if (result < 0) return -1;

    git_oid oid;

    result = convert_hex_bin(hash.get_hash(), oid);
    if (result < 0) return -1;

    Guard<git_revwalk> walker;
    Guard<git_commit> commit;

    git_revwalk_new(walker.get_p(), m_repo);
    git_revwalk_sorting(walker.get(), GIT_SORT_TOPOLOGICAL);
    git_revwalk_push(walker.get(), &oid);

    const char *commit_message;
    const git_signature *commit_signature;
    git_time_t commit_time;

    while (git_revwalk_next(&oid, walker.get()) == 0)
    {
        if (git_commit_lookup(commit.get_p(), m_repo, &oid) != 0)
        {
            return -2;
        }

        commit_message = git_commit_message(commit.get());
        commit_signature = git_commit_committer(commit.get());
        commit_time = git_commit_time(commit.get());

        std::time_t commit_time_t = static_cast<std::time_t>(commit_time);
        std::string commit_time_str = std::asctime(std::localtime(&commit_time_t));

        auto commit_info = std::make_shared<git::Commit>();

        commit_info->set_message(commit_message);
        commit_info->set_author(commit_signature->name);
        commit_info->set_email(commit_signature->email);
        commit_info->set_date_time(std::chrono::system_clock::from_time_t(commit_time_t));

        result = convert_bin_hex(oid, commit_info->get_hash().get_hash());
        if (result < 0) return -2;

        walk_commit->new_commit(self(), commit_info);
        commit.reset();
    }

    return 0;
    // self()->cmd_start();
}

int GitImpl::diff(const git::CommitHash commit_hash, std::shared_ptr<git::Diff> diff)
{
    Guard<git_tree> commit_tree;
    Guard<git_tree> parent_tree;
    bool has_parent = true;

    int result = treeish_to_tree(commit_tree, m_repo, commit_hash.get_hash().c_str());
    if (result < 0) return -1;

    git::CommitHash parent_hash;
    result = get_parent_commit(commit_hash, parent_hash);
    if (result < 0)
        has_parent = false;
    else
    {
        result = treeish_to_tree(parent_tree, m_repo, parent_hash.get_hash().c_str());
        if (result < 0) return -1;
    }

    Guard<git_diff> the_diff;
    git_diff_options diffopts;

    result = git_diff_options_init(&diffopts, GIT_DIFF_OPTIONS_VERSION);
    if (result < 0) return -1;

    // diffopts.id_abbrev = 40;

    if (has_parent)
        result = git_diff_tree_to_tree(the_diff.get_p(), m_repo, parent_tree.get(), commit_tree.get(), &diffopts);
    else
        result = git_diff_tree_to_tree(the_diff.get_p(), m_repo, nullptr, commit_tree.get(), &diffopts);

    if (result < 0) return -1;

    Guard<git_diff_stats> diff_stats;

    result = git_diff_get_stats(diff_stats.get_p(), the_diff.get());
    if (result < 0) return -1;

    /*diff_file_stats *filestats;

    size_t files_changed;
    size_t insertions;
    size_t deletions;
    size_t renames;

    size_t max_name;
    size_t max_filestat;
    int max_digits; */
    diff->set_files_changed(static_cast<unsigned int>(git_diff_stats_files_changed(diff_stats.get())));
    diff->set_insertions(static_cast<unsigned int>(git_diff_stats_insertions(diff_stats.get())));
    diff->set_deletions(static_cast<unsigned int>(git_diff_stats_deletions(diff_stats.get())));
    diff->set_renames(static_cast<unsigned int>(git_diff_stats_renames(diff_stats.get())));
    return 0;
}

int GitImpl::clone(const std::string &url, const std::string &path, const std::string &branch)
{
    std::string new_ref;
    int result = 0;

    self()->debug(1, "[GitImpl::clone] begin ...]");

    if (url.find("https:") == 0)
    {
        self()->debug(1, "[GitImpl::clone] https]");
        self()->cmd_start();
        self()->open_time();

        if (branch.empty())
            result = git_clone(&m_repo, url.c_str(), path.c_str(), nullptr);
        else
        {
            git_clone_options opts = GIT_CLONE_OPTIONS_INIT;
            opts.checkout_branch = new_ref.c_str();

            result = git_clone(&m_repo, url.c_str(), path.c_str(), &opts);
        }
    }
    else if ((url.find("ssh:") == 0))
    {
        self()->debug(1, "[GitImpl::clone] ssh]");
        if (!is_ssh_agent_running()) return check_error(-1, "Only authentication via an ssh agent is supported", false);

        self()->cmd_start();
        self()->open_time();

        git_clone_options opts = GIT_CLONE_OPTIONS_INIT;
        if (!branch.empty()) opts.checkout_branch = new_ref.c_str();
        // opts.fetch_opts.callbacks.connect = &Remote::Callbacks::connect;
        // opts.fetch_opts.callbacks.disconnect = &Remote::Callbacks::disconnect;
        opts.fetch_opts.callbacks.sideband_progress = &GitImpl::libgit2_sideband_progress_cb;
        opts.fetch_opts.callbacks.credentials = &GitImpl::libgit2_credentials_cb;
        // opts.fetch_opts.callbacks.certificate_check = &Remote::Callbacks::certificate;
        opts.fetch_opts.callbacks.transfer_progress = &GitImpl::libgit2_transfer_progress_cb;
        opts.fetch_opts.callbacks.update_tips = &GitImpl::libgit2_update_tips_cb;
        opts.fetch_opts.callbacks.pack_progress = &GitImpl::libgit2_pack_progress_cb;
        // opts.fetch_opts.callbacks.resolve_url = &Remote::Callbacks::url;
        opts.fetch_opts.callbacks.payload = this;
        // opts.bare = bare;

        result = git_clone(&m_repo, url.c_str(), path.c_str(), &opts);
    }
    else
        return check_error(-1, "Unknown protocol.");

    return check_error(result, "Clone failed");
}

int GitImpl::checkout(const std::string &branch, bool force)
{
    Guard<git_annotated_commit> annotated_commit;
    Guard<git_object> treeish;
    Guard<git_commit> target_commit;
    Guard<git_reference> ref;
    Guard<git_reference> branch_ref;
    Guard<git_reference> input_branch_ref;
    std::string new_ref = branch;

    self()->cmd_start();

    int result = resolve_ref(input_branch_ref.get_p(), annotated_commit.get_p(), branch);
    if (result < 0)
    {
        self()->debug(0, "branch not found : " + branch);
        // In the case where the content of branch doesn't have the full qualifier,
        // try to to guess

        result = find_ref(input_branch_ref.get_p(), annotated_commit.get_p(), branch, new_ref);
        if (result < 0) return check_error(result);
    }

    result = git_commit_lookup(target_commit.get_p(), m_repo, git_annotated_commit_id(annotated_commit.get()));
    const git_oid *oid = git_commit_id(target_commit.get());
    std::string oid_str;
    result = convert_bin_hex(*oid, oid_str);

    git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
    if (force)
        opts.checkout_strategy = GIT_CHECKOUT_FORCE;
    else
        opts.checkout_strategy = GIT_CHECKOUT_SAFE;

    auto t_commit = static_cast<git_object *>(static_cast<void *>(target_commit.get()));
    result = git_checkout_tree(m_repo, t_commit, &opts);
    if (result < 0) return check_error(result);

    if (git_annotated_commit_ref(annotated_commit.get()))
    {
        const char *target_head = nullptr;

        result = git_reference_lookup(ref.get_p(), m_repo, git_annotated_commit_ref(annotated_commit.get()));
        if (result < 0) return check_error(result);

        if (git_reference_is_remote(ref.get()))
        {
            result =
                git_branch_create_from_annotated(branch_ref.get_p(), m_repo, branch.c_str(), annotated_commit.get(), 0);
            if (result < 0) return check_error(result);

            target_head = git_reference_name(branch_ref.get());

            // if (git_reference_is_branch(input_branch_ref.get()))
            // git_
            const char *branch_name = nullptr;
            result = git_branch_name(&branch_name, input_branch_ref.get());
            if (result < 0)
                check_error(result, "can't get the name of the branch");
            else
            {
                result = git_branch_set_upstream(branch_ref.get(), branch_name);
                if (result < 0) check_error(result, "set branch upstream");
            }
        }
        else
        {
            target_head = git_annotated_commit_ref(annotated_commit.get());
        }

        result = git_repository_set_head(m_repo, target_head);
        return check_error(result);
    }
    else
    {
        result = git_repository_set_head_detached_from_annotated(m_repo, annotated_commit.get());
        return check_error(result);
    }
}

int GitImpl::reset(const git::CommitHash &commit, git::ResetType type)
{
    if (m_repo == nullptr) return -1;

    int result = 0;
    git_reset_t reset_type = GIT_RESET_SOFT;

    switch (type)
    {
        case git::ResetType::NOT_SET: return -2;
        case git::ResetType::HARD: reset_type = GIT_RESET_HARD; break;
        case git::ResetType::MIXED: reset_type = GIT_RESET_MIXED; break;
        case git::ResetType::SOFT: reset_type = GIT_RESET_SOFT; break;
        default: return -3;
    }

    Guard<git_commit> g_commit;
    git_oid oid_commit;

    result = convert_hex_bin(commit.get_hash(), oid_commit);
    if (result < 0) return check_error(0);

    // get the actual commit structure
    result = git_commit_lookup(g_commit.get_p(), m_repo, &oid_commit);
    if (result < 0) return check_error(result);

    auto t_commit = static_cast<git_object *>(static_cast<void *>(g_commit.get()));
    return git_reset(m_repo, t_commit, reset_type, nullptr);
}

int GitImpl::fastforward(const git::CommitHash &commit)
{
    git_checkout_options ff_checkout_options = GIT_CHECKOUT_OPTIONS_INIT;
    Guard<git_reference> target_ref;
    Guard<git_reference> new_target_ref;
    Guard<git_object> target;
    int result = 0;
    git_oid target_oid;

    assert(m_repo != nullptr);

    result = convert_hex_bin(commit.get_hash(), target_oid);
    if (result < 0) return check_error(result);

    // HEAD exists, just lookup and resolve
    result = git_repository_head(target_ref.get_p(), m_repo);
    if (result != 0) return check_error(result, "failed to get HEAD reference");

    // Lookup the target object
    result = git_object_lookup(target.get_p(), m_repo, &target_oid, GIT_OBJECT_COMMIT);
    if (result != 0) return check_error(result, "failed to lookup OID " + commit.get_hash());

    // Checkout the result so the workdir is in the expected state
    ff_checkout_options.checkout_strategy = GIT_CHECKOUT_SAFE;
    result = git_checkout_tree(m_repo, target.get(), &ff_checkout_options);
    if (result != 0) return check_error(result, "failed to checkout HEAD reference");

    // Move the target reference to the target OID
    result = git_reference_set_target(new_target_ref.get_p(), target_ref.get(), &target_oid, nullptr);
    if (result != 0) return check_error(result, "failed to move HEAD reference");

    return 0;
}

int GitImpl::get_last_commit(git::CommitHash &commit)
{
    if (m_repo == nullptr) return -1;

    int result = 0;
    Guard<git_commit> g_commit;
    git_oid oid_last_commit;

    self()->cmd_start();

    // resolve HEAD into a SHA1
    result = git_reference_name_to_id(&oid_last_commit, m_repo, "HEAD");
    if (result < 0) return check_error(result);

    // get the actual commit structure
    result = git_commit_lookup(g_commit.get_p(), m_repo, &oid_last_commit);
    if (result < 0) return check_error(result);

    std::string hash;
    result = convert_bin_hex(oid_last_commit, hash);
    if (result == 0) commit.set_hash(hash);

    return check_error(result);
}

int GitImpl::get_parent_commit(const git::CommitHash &commit, git::CommitHash &parent, int nth_parent)
{
    if (m_repo == nullptr) return -1;

    Guard<git_commit> g_commit;
    Guard<git_commit> cur_commit;
    Guard<git_commit> parent_commit;
    git_oid oid_commit;

    self()->cmd_start();

    if (nth_parent == 0)
    {
        parent = commit;
        return check_error(0);
    }

    int result = convert_hex_bin(commit.get_hash(), oid_commit);
    if (result < 0) return check_error(0);

    // get the actual commit structure
    result = git_commit_lookup(cur_commit.get_p(), m_repo, &oid_commit);
    if (result < 0) return check_error(result);

    unsigned int count = 0;

    for (int idx = 0; idx < nth_parent; ++idx)
    {
        count = git_commit_parentcount(cur_commit.get());
        if (count <= 0) return check_error(-2);

        parent_commit.reset();
        result = git_commit_parent(parent_commit.get_p(), cur_commit.get(), 0);
        if (result < 0) return check_error(result);

        cur_commit = parent_commit;
    }

    const git_oid *parent_commit_id = git_commit_id(parent_commit.get());
    if (parent_commit_id == nullptr) check_error(-3);

    std::string hash;
    result = convert_bin_hex(*parent_commit_id, hash);
    if (result == 0) parent.set_hash(hash);

    return check_error(result);
}

int GitImpl::is_dirty(bool &dirty)
{
    if (m_repo == nullptr) return -1;

    Guard<git_status_list> status;
    git_status_options statusopt = GIT_STATUS_OPTIONS_INIT;

    self()->cmd_start();

    statusopt.show = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
    statusopt.flags = GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX | GIT_STATUS_OPT_SORT_CASE_SENSITIVELY;

    int result = git_status_list_new(status.get_p(), m_repo, &statusopt);
    if (result < 0) return check_error(result);

    std::size_t count = git_status_list_entrycount(status.get());
    dirty = (count != 0);
    return check_error(0);
}

int GitImpl::is_detached(bool &detached)
{
    if (m_repo == nullptr) return -1;

    int result = git_repository_head_detached(m_repo);
    if (result < 0) return result;

    if (result == 1)
        detached = true;
    else
        detached = false;
    return 0;
}

int GitImpl::get_status(git::RepoStatus &repo_status)
{
    if (m_repo == nullptr) return -1;

    const git_status_entry *status_entry = nullptr;
    Guard<git_status_list> status_list;
    git_status_options statusopt = GIT_STATUS_OPTIONS_INIT;

    self()->cmd_start();

    statusopt.show = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
    statusopt.flags =
        GIT_STATUS_OPT_INCLUDE_UNTRACKED | GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX | GIT_STATUS_OPT_SORT_CASE_SENSITIVELY;

    int result = git_status_list_new(status_list.get_p(), m_repo, &statusopt);
    if (result < 0) return check_error(result);

    std::size_t count = git_status_list_entrycount(status_list.get());

    for (std::size_t idx = 0; idx < count; ++idx)
    {
        status_entry = git_status_byindex(status_list.get(), idx);

        handle_status_entry(repo_status, status_entry);
    }
    return check_error(0);
}

int GitImpl::handle_status_entry(git::RepoStatus &repo_status, const git_status_entry *status_entry)
{
    std::shared_ptr<git::Status> status = std::make_shared<git::Status>();
    int result = 0;

    if (status_entry->status == GIT_STATUS_CURRENT)
        result = handle_status_entry_current(repo_status, status, status_entry);

    else if (status_entry->status < GIT_STATUS_WT_NEW)
        result = handle_status_entry_index(repo_status, status, status_entry);
    else if (status_entry->status < GIT_STATUS_IGNORED)
        result = handle_status_entry_work_dir(repo_status, status, status_entry);
    else if (status_entry->status == GIT_STATUS_IGNORED)
        result = handle_status_entry_ignored(repo_status, status, status_entry);
    else if (status_entry->status == GIT_STATUS_CONFLICTED)
        result = handle_status_entry_conflicted(repo_status, status, status_entry);
    else
        return -1;

    repo_status.add(status);
    return 0;
}

int GitImpl::handle_status_entry_current(git::RepoStatus &repo_status, std::shared_ptr<git::Status> status,
                                         const git_status_entry *status_entry)
{
    status->set_type(git::StatusType::CURRENT);

    return 0;
}

int GitImpl::handle_status_entry_index(git::RepoStatus &repo_status, std::shared_ptr<git::Status> status,
                                       const git_status_entry *status_entry)
{
    status->set_type(git::StatusType::INDEX);

    return 0;
}

int GitImpl::handle_status_entry_work_dir(git::RepoStatus &repo_status, std::shared_ptr<git::Status> status,
                                          const git_status_entry *status_entry)
{
    status->set_type(git::StatusType::WORKING_DIR);

    int result = 0;
    int local_result = from_to(status_entry->index_to_workdir, status->get_diff_delta());
    if (local_result < 0) --result;

    local_result = from_to(status_entry->status, status);
    if (local_result < 0) --result;

    return result;
}

int GitImpl::handle_status_entry_conflicted(git::RepoStatus &repo_status, std::shared_ptr<git::Status> status,
                                            const git_status_entry *status_entry)
{
    status->set_type(git::StatusType::CONFLICTED);

    return 0;
}

int GitImpl::handle_status_entry_ignored(git::RepoStatus &repo_status, std::shared_ptr<git::Status> status,
                                         const git_status_entry *status_entry)
{
    status->set_type(git::StatusType::IGNORED);

    return 0;
}

int GitImpl::from_to(git_status_t status, std::shared_ptr<git::Status> status_ptr)
{
    switch (status)
    {
        case GIT_STATUS_INDEX_NEW:
        case GIT_STATUS_WT_NEW: status_ptr->set_sub_type(git::StatusSubType::NEW); break;

        case GIT_STATUS_INDEX_MODIFIED:
        case GIT_STATUS_WT_MODIFIED: status_ptr->set_sub_type(git::StatusSubType::MODIFIED); break;

        case GIT_STATUS_INDEX_DELETED:
        case GIT_STATUS_WT_DELETED: status_ptr->set_sub_type(git::StatusSubType::DELETED); break;

        case GIT_STATUS_INDEX_RENAMED:
        case GIT_STATUS_WT_RENAMED: status_ptr->set_sub_type(git::StatusSubType::RENAMED); break;

        case GIT_STATUS_INDEX_TYPECHANGE:
        case GIT_STATUS_WT_TYPECHANGE: status_ptr->set_sub_type(git::StatusSubType::TYPECHANGE); break;

        case GIT_STATUS_WT_UNREADABLE: status_ptr->set_sub_type(git::StatusSubType::UNREADABLE); break;

        default: return -1;
    }
    return 0;
}

int GitImpl::from_to(const git_diff_delta *delta, git::DiffDelta &diff_delta)
{
    diff_delta.set_file_count(delta->nfiles);
    diff_delta.set_similatiry(delta->similarity);

    int result = 0;

    int local_result = from_to(delta->old_file, diff_delta.get_old_file());
    if (local_result < 0) --result;

    local_result = from_to(delta->new_file, diff_delta.get_new_file());
    if (local_result < 0) --result;

    return result;
}

int GitImpl::from_to(const git_diff_file &file, git::DiffFile &diff_file)
{
    std::string id;
    int result = convert_bin_hex(file.id, id);
    if (result == 0) diff_file.set_id(id);

    diff_file.set_path(file.path);
    diff_file.set_size(file.size);

    git::FileMode mode = git::FileMode::NOT_SET;

    switch (file.mode)
    {
        case GIT_FILEMODE_UNREADABLE: mode = git ::FileMode::NEW; break;
        case GIT_FILEMODE_TREE: mode = git ::FileMode::TREE; break;
        case GIT_FILEMODE_BLOB: mode = git ::FileMode::BLOB; break;
        case GIT_FILEMODE_BLOB_EXECUTABLE: mode = git ::FileMode::BLOB_EXECUTABLE; break;
        case GIT_FILEMODE_LINK: mode = git ::FileMode::LINK; break;
        case GIT_FILEMODE_COMMIT: mode = git ::FileMode::COMMIT; break;
        default: mode = git::FileMode::NOT_SET;
    }

    diff_file.set_mode(mode);

    return result;
}

int GitImpl::check_error(int result, const std::string &action, bool show_result)
{
    self()->cmd_end();

    if (result == 0) return 0;

    const git_error *error = git_error_last();

    std::ostringstream oss;
    // oss << "ERROR " << result << " : " << action;
    oss << action;
    if (show_result)
    {
        oss << " (" << result << ").";
        if (error && error->message)
        {
            oss << " - " << error->message;
        }
    }
    self()->error(oss.str());

    return result;
}

Git *GitImpl::self() const
{
    return m_self;
}

int GitImpl::libgit2_credentials_cb(git_credential **out, const char *url, const char *name, unsigned int types,
                                    void *payload)
{
    const git_error *error = git_error_last();
    if (error && error->klass == GIT_ERROR_SSH) return -1;

    auto self = static_cast<GitImpl *>(payload);

    if (self->is_ssh_agent_running())
    {
        self->self()->debug(0, "[GitImpl::libgit2_credentials_cb] agent is running");

        std::string agent_id_path = libssh2::SSH::get_dflt_agent_identity_path();
        if (agent_id_path.empty())
            return git_credential_ssh_key_from_agent(out, name);
        else
        {
            std::ostringstream oss;

            oss << "[GitImpl::libgit2_credentials_cb] use custom agent with path '" << agent_id_path << "'";
            self->self()->debug(0, oss.str());
            return git_credential_ssh_key_from_custom_agent(out, name, agent_id_path.c_str());
        }
    }
    else
        self->self()->debug(0, "[GitImpl::libgit2_credentials_cb] NO agent is running");

    return -177;
}

int GitImpl::libgit2_sideband_progress_cb(const char *str, int len, void *data)
{
    auto impl = static_cast<GitImpl *>(data);

    if (impl == nullptr) return 0;

    std::string txt(str, str + len);

    int result = impl->self()->handle_sideband_progress(txt);
    return result;
}

int GitImpl::libgit2_transfer_progress_cb(const git_indexer_progress *stats, void *payload)
{
    auto impl = static_cast<GitImpl *>(payload);

    if (impl == nullptr) return 0;

    git::Progress progress;

    // std::cout << "[libgit2_transfer_progress_cb]" << std::endl;

    if (stats->received_objects == stats->total_objects)
    {
        progress.set_fetch_step(git::FetchStep::RESOLVING);

        if (stats->indexed_deltas == stats->total_deltas)
        {
            progress.set_done(true);
            progress.set_percentage(git::Progress::MAX_PERCENTAGE);
        }
        else
        {
            double percentage = (100.0 * stats->indexed_deltas) / stats->total_deltas;

            progress.set_done(false);
            progress.set_percentage(static_cast<int>(percentage));
        }
        // std::cout << "Resolving deltas " << stats->indexed_deltas << "/" << stats->total_deltas << std::endl;
    }
    else if (stats->total_objects > 0)
    {
        progress.set_fetch_step(git::FetchStep::RECEIVING);
        // std::cout << "Received " << stats->received_objects << "/" << stats->total_objects << " objects "
        //          << "(" << stats->indexed_objects << ") in " << stats->received_bytes << std::endl;
        if (stats->received_objects == stats->total_objects)
        {
            progress.set_done(true);
            progress.set_percentage(git::Progress::MAX_PERCENTAGE);
        }
        else
        {
            double percentage = (100.0 * stats->received_objects) / stats->total_objects;

            progress.set_done(false);
            progress.set_percentage(static_cast<int>(percentage));
        }
    }

    if (impl->self()->get_progress_callback() != nullptr)
        impl->self()->get_progress_callback()->git_progress_notif(progress);

    return 0;
}

int GitImpl::libgit2_update_tips_cb(const char *refname, const git_oid *a, const git_oid *b, void *data)
{
    std::string a_str;
    std::string b_str;
    auto self = static_cast<GitImpl *>(data);
    std::ostringstream oss;
    git::UpdateTip update_tip;

    self->convert_bin_hex(*b, b_str);
    update_tip.set_ref_name(refname);

    if (git_oid_is_zero(a))
    {
        // oss << "[new]     " << b_str << " " << refname;
        // std::cout << oss.str() << std::endl;
        update_tip.set_type(git::UpdateTipType::NEW);
        update_tip.set_new_oid(b_str);
    }
    else
    {
        update_tip.set_type(git::UpdateTipType::UPDATE);
        self->convert_bin_hex(*a, a_str);
        update_tip.set_new_oid(b_str);
        update_tip.set_new_oid(b_str);
        // oss << "[updated] " << a_str << ".." << b_str << " " << refname;
        // std::cout << oss.str() << std::endl;
    }
    return 0;
}

int GitImpl::libgit2_pack_progress_cb(int stage, uint32_t current, uint32_t total, void *payload)
{
    std::cout << "[libgit2_pack_progress_cb]" << std::endl;
    return 0;
}

bool GitImpl::is_ssh_agent_running()
{
    bool present = m_ssh.is_agent_present();

    if (present) self()->debug(0, "SSH agent detected");

    return present;
}

int GitImpl::merge_analysis(const std::vector<std::string> &refs, git::MergeAnalysisResult &merge_analysis_result,
                            std::vector<git::CommitHash> &commits)
{
    git_repository_state_t state = GIT_REPOSITORY_STATE_NONE;
    git_merge_analysis_t analysis = GIT_MERGE_ANALYSIS_NONE;
    git_merge_preference_t preference = GIT_MERGE_PREFERENCE_NONE;
    git_annotated_commit *annotated = nullptr;
    git::CommitHash commit;
    int result = 0;

    if (m_repo == nullptr) return -1;

    state = static_cast<git_repository_state_t>(git_repository_state(m_repo));
    if (state != GIT_REPOSITORY_STATE_NONE)
    {
        return -1;
    }

    std::vector<git_annotated_commit *> annotated_vec;
    std::vector<git_oid> oids;
    const git_oid *target_oid = nullptr;
    std::string hash;

    for (auto &ref : refs)
    {
        result = resolve_ref(&annotated, ref);
        if (result == GIT_OK)
        {
            target_oid = git_annotated_commit_id(annotated);
            oids.push_back(*target_oid);
            annotated_vec.push_back(annotated);

            result = convert_bin_hex(*target_oid, hash);
            if (result == 0)
            {
                commit.set_hash(hash);
                commits.push_back(commit);
            }
        }
    }

    result = git_merge_analysis(&analysis, &preference, m_repo, (const git_annotated_commit **)annotated_vec.data(),
                                annotated_vec.size());

    for (auto annotated : annotated_vec) git_annotated_commit_free(annotated);

    if (analysis & GIT_MERGE_ANALYSIS_UP_TO_DATE)
        merge_analysis_result = git::MergeAnalysisResult::UP_TO_DATE;
    else if (analysis & GIT_MERGE_ANALYSIS_NORMAL)
    {
        if (analysis & GIT_MERGE_ANALYSIS_FASTFORWARD)
            merge_analysis_result = git::MergeAnalysisResult::FASTFORWARD;
        else
            merge_analysis_result = git::MergeAnalysisResult::NORMAL;
    }
    else if (analysis & GIT_MERGE_ANALYSIS_FASTFORWARD)
        merge_analysis_result = git::MergeAnalysisResult::FASTFORWARD;
    else if (analysis & GIT_MERGE_ANALYSIS_UNBORN)
        merge_analysis_result = git::MergeAnalysisResult::UNBORN;
    else
        merge_analysis_result = git::MergeAnalysisResult::NONE;
    return 0;
}

int GitImpl::fetch(const std::string &remote_str)
{
    if (m_repo == nullptr) return -1;

    Guard<git_remote> remote;
    std::string remote_name;
    int result = 0;

    if (!remote_str.empty())
    {
        result = git_remote_lookup(remote.get_p(), m_repo, remote_str.c_str());
        if (result < 0)
        {
            // The remote is not known
            self()->error("The given remote is not known : " + remote_str);
            return -1;
        }

        remote_name = git_remote_name(remote.get());
    }
    else
    {
        git::Branches branches;

        result = get_branches(branches);
        if (result < 0)
        {
            self()->error("Couldn't get the branches for this git repo");
            return -1;
        }

        if (branches.size() == 0)
        {
            self()->error("No branches found for this git repo");
            return -1;
        }

        branches.sort();

        remote_name = branches.get()[0]->get_remote_name();

        result = git_remote_lookup(remote.get_p(), m_repo, remote_name.c_str());
        if (result < 0)
        {
            // The remote is not known
            self()->error("The given remote is not known : " + remote_name);
            return -1;
        }
    }

    git_fetch_options fetch_opts = GIT_FETCH_OPTIONS_INIT;

    /* Set up the callbacks (only update_tips for now) */
    // fetch_opts.callbacks.update_tips = &update_cb;
    fetch_opts.callbacks.sideband_progress = &GitImpl::libgit2_sideband_progress_cb;
    // fetch_opts.callbacks.transfer_progress = transfer_progress_cb;
    fetch_opts.callbacks.credentials = &GitImpl::libgit2_credentials_cb;
    fetch_opts.callbacks.payload = this;

    result = git_remote_fetch(remote.get(), nullptr, &fetch_opts, "fetch");
    if (result < 0)
    {
        self()->error("Fetch failed");
        return -1;
    }

    const git_indexer_progress *stats = git_remote_stats(remote.get());

    //! \TODO what to do with the stats;

    return result;
}

int GitImpl::resolve_ref(git_reference **ref, const std::string &ref_str)
{
    Guard<git_object> git_obj;
    int result = 0;

    assert(ref != nullptr);
    assert(m_repo != nullptr);

    result = git_reference_dwim(ref, m_repo, ref_str.c_str());
    if (result == GIT_OK) return 0;

    result = git_revparse_single(git_obj.get_p(), m_repo, ref_str.c_str());
    if (result == GIT_OK) return 0;

    return result;
}

int GitImpl::resolve_ref(git_annotated_commit **commit, const std::string &ref)
{
    git_reference *git_ref = nullptr;
    git_object *git_obj = nullptr;
    int result = 0;

    assert(commit != nullptr);
    assert(m_repo != nullptr);

    result = git_reference_dwim(&git_ref, m_repo, ref.c_str());
    if (result == GIT_OK)
    {
        const char *name = git_reference_name(git_ref);

        //! \TODO remote this
        const char *branch_name = nullptr;
        git_branch_name(&branch_name, git_ref);

        git_annotated_commit_from_ref(commit, m_repo, git_ref);
        git_reference_free(git_ref);
        return 0;
    }

    result = git_revparse_single(&git_obj, m_repo, ref.c_str());
    if (result == GIT_OK)
    {
        result = git_annotated_commit_lookup(commit, m_repo, git_object_id(git_obj));
        git_object_free(git_obj);
    }

    return result;
}

int GitImpl::resolve_ref(git_reference **ref, git_annotated_commit **commit, const std::string &ref_str)
{
    Guard<git_object> git_obj;
    int result = 0;

    assert(commit != nullptr);
    assert(ref != nullptr);
    assert(m_repo != nullptr);

    result = git_reference_dwim(ref, m_repo, ref_str.c_str());
    if (result == GIT_OK)
    {
        git_annotated_commit_from_ref(commit, m_repo, *ref);
        return 0;
    }

    result = git_revparse_single(git_obj.get_p(), m_repo, ref_str.c_str());
    if (result == GIT_OK)
    {
        result = git_annotated_commit_lookup(commit, m_repo, git_object_id(git_obj.get()));
    }

    return result;
}

int GitImpl::find_ref(git_annotated_commit **commit, const std::string &ref, std::string &new_ref)
{
    std::vector<git::Remote> remotes;
    int found_remotes = 0;

    int result = get_remotes(remotes);
    if (result != GIT_OK) return result;

    for (auto &remote : remotes)
    {
        new_ref = "refs/remotes/" + remote.get_name() + "/" + ref;

        result = resolve_ref(commit, new_ref);
        if (result == GIT_OK)
        {
            self()->debug(0, "found branch : " + new_ref);
            ++found_remotes;
        }
    }
    if (found_remotes == 1) return 0;
    return -1;
}

int GitImpl::find_ref(git_reference **ref, git_annotated_commit **commit, const std::string &ref_str,
                      std::string &new_ref)
{
    std::vector<git::Remote> remotes;
    int found_remotes = 0;

    int result = get_remotes(remotes);
    if (result != GIT_OK) return result;

    for (auto &remote : remotes)
    {
        new_ref = "refs/remotes/" + remote.get_name() + "/" + ref_str;

        result = resolve_ref(ref, commit, new_ref);
        if (result == GIT_OK)
        {
            self()->debug(0, "found branch : " + new_ref);
            ++found_remotes;
        }
    }
    if (found_remotes == 1) return 0;
    return -1;
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

int GitImpl::convert_hex_bin(const std::string &hex_str, git_oid &oid)
{
    return git_oid_fromstrp(&oid, hex_str.c_str());
}

const std::string &GitImpl::get_version()
{
    return s_get_version();
}

const std::string &GitImpl::get_lib_name()
{
    return s_get_lib_name();
}

void GitImpl::convert(git::BranchType branch_type, git_branch_t &list_flags)
{
    switch (branch_type)
    {
        case git::BranchType::ALL: list_flags = GIT_BRANCH_ALL; break;
        case git::BranchType::LOCAL: list_flags = GIT_BRANCH_LOCAL; break;
        case git::BranchType::REMOTE: list_flags = GIT_BRANCH_REMOTE; break;
        default: list_flags = GIT_BRANCH_LOCAL;
    }
}

void GitImpl::set_agent_identity_path(const std::string &agent_identity_path)
{
    m_agent_identity_path = agent_identity_path;
}

const std::string &GitImpl::get_agent_identity_path() const
{
    return m_agent_identity_path;
}

void GitImpl::set_logger_if(std::shared_ptr<log::Logger_if> logger_if)
{
    m_ssh.set_logger_if(logger_if);
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

} // namespace esys::repo::libgit2
