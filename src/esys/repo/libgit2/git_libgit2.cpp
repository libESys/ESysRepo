/*!
 * \file esys/repo/libgit2/git_libgit2.cpp
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
#include "esys/repo/libgit2/git.h"
#include "esys/repo/libgit2/gitimpl.h"

namespace esys
{

namespace repo
{

namespace libgit2
{

Git::Git()
    : GitBase()
{
    m_impl = std::make_unique<GitImpl>(this);
}

Git::~Git() = default;

int Git::open(const std::string &folder)
{
    return get_impl()->open(folder);
}

bool Git::is_open()
{
    return get_impl()->is_open();
}

int Git::close()
{
    return get_impl()->close();
}

int Git::get_remotes(std::vector<git::Remote> &remotes)
{
    return get_impl()->get_remotes(remotes);
}

int Git::get_branches(std::vector<git::Branch> &branches, git::BranchType branch_type)
{
    return get_impl()->get_branches(branches, branch_type);
}

int Git::clone(const std::string &url, const std::string &path)
{
    return get_impl()->clone(url, path);
}

int Git::checkout(const std::string &branch, bool force)
{
    return get_impl()->checkout(branch, force);
}

int Git::get_last_commit(git::Commit &commit)
{
    return get_impl()->get_last_commit(commit);
}

int Git::is_dirty(bool &dirty)
{
    return get_impl()->is_dirty(dirty);
}

int Git::get_status(git::RepoStatus &repo_status)
{
    return m_impl->get_status(repo_status);
}

bool Git::is_ssh_agent_running()
{
    return m_impl->is_ssh_agent_running();
}

const std::string &Git::get_version()
{
    return m_impl->get_version();
}

const std::string &Git::get_lib_name()
{
    return m_impl->get_lib_name();
}

const std::string &Git::s_get_version()
{
    return GitImpl::s_get_version();
}

const std::string &Git::s_get_lib_name()
{
    return GitImpl::s_get_lib_name();
}

const std::string &Git::s_get_ssh_version()
{
    return GitImpl::s_get_ssh_version();
}

const std::string &Git::s_get_ssh_lib_name()
{
    return GitImpl::s_get_ssh_lib_name();
}

GitImpl *Git::get_impl() const
{
    return m_impl.get();
}

} // namespace libgit2

} // namespace repo

} // namespace esys
