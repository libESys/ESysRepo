/*!
 * \file esys/repo/libgit2/git_libgit2.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2021 Michel Gillet
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

std::shared_ptr<GitBase> Git::new_ptr()
{
    return std::make_shared<Git>();
}

Git::Git()
    : GitBase()
{
    m_impl = std::make_unique<GitImpl>(this);
}

Git::~Git() = default;

int Git::open(const std::string &folder)
{
    set_folder(folder);
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

int Git::get_branches(git::Branches &branches, git::BranchType branch_type)
{
    return get_impl()->get_branches(branches, branch_type);
}

int Git::clone(const std::string &url, const std::string &path, const std::string &branch)
{
    set_url(url);
    return get_impl()->clone(url, path, branch);
}

int Git::checkout(const std::string &branch, bool force)
{
    return get_impl()->checkout(branch, force);
}

int Git::reset(const git::Commit &commit, git::ResetType type)
{
    return get_impl()->reset(commit, type);
}

int Git::fastforward(const git::Commit &commit)
{
    return get_impl()->fastforward(commit);
}

int Git::get_last_commit(git::Commit &commit)
{
    return get_impl()->get_last_commit(commit);
}

int Git::get_parent_commit(const git::Commit &commit, git::Commit &parent, int nth_parent)
{
    return get_impl()->get_parent_commit(commit, parent, nth_parent);
}

int Git::is_dirty(bool &dirty)
{
    return get_impl()->is_dirty(dirty);
}

int Git::is_detached(bool &detached)
{
    return get_impl()->is_detached(detached);
}

int Git::get_status(git::RepoStatus &repo_status)
{
    return m_impl->get_status(repo_status);
}

bool Git::is_ssh_agent_running()
{
    return m_impl->is_ssh_agent_running();
}

int Git::merge_analysis(const std::vector<std::string> &refs, git::MergeAnalysisResult &merge_analysis_result,
                        std::vector<git::Commit> &commits)
{
    return m_impl->merge_analysis(refs, merge_analysis_result, commits);
}

int Git::fetch(const std::string &remote)
{
    return m_impl->fetch(remote);
}

bool Git::has_branch(const std::string &name, git::BranchType branch_type)
{
    return m_impl->has_branch(name, branch_type);
}

void Git::set_url(const std::string &url)
{
    m_url = url;
}

const std::string &Git::get_url()
{
    return m_url;
}

void Git::set_folder(const std::string &folder)
{
    m_folder = folder;
}

const std::string &Git::get_folder()
{
    return m_folder;
}

const std::string &Git::get_version()
{
    return m_impl->get_version();
}

const std::string &Git::get_lib_name()
{
    return m_impl->get_lib_name();
}

void Git::debug(int level, const std::string &msg)
{
    // log::ConsoleLockGuard<log::User> lock(this);
    //! \TODO must be fixed to allow writing after all console is written

    GitBase::debug(level, msg);
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
