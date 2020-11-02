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

#include <iostream>

namespace esys
{

namespace repo
{

namespace libgit2
{

std::unique_ptr<LibGit2> GitImpl::s_libgt2;

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
        if (result == 1)
            branch.set_is_head(true);

        branches.push_back(branch);
    }

    return 0;
}

int GitImpl::check_error(int result, const std::string &action)
{
    const git_error *error = git_error_last();
    if (!result) return 0;

    std::cerr << "ERROR " << result << " : " << action << " - ";

    std::cerr << ((error && error->message) ? error->message : "???") << std::endl;

    return result;
}

Git *GitImpl::self() const
{
    return m_self;
}

} // namespace libgit2

} // namespace repo

} // namespace esys
