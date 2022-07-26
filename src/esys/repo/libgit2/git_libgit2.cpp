/*!
 * \file esys/repo/libgit2/git_libgit2.cpp
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
#include "esys/repo/libgit2/git.h"
#include "esys/repo/libgit2/gitimpl.h"

namespace esys::repo::libgit2
{

bool Git::s_detect_ssh_agent_done = false;
bool Git::s_ssh_agent_running = false;

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

Result Git::open(const std::string &folder)
{
    set_folder(folder);
    return get_impl()->open(folder);
}

bool Git::is_open()
{
    return get_impl()->is_open();
}

Result Git::close()
{
    return get_impl()->close();
}

Result Git::get_remotes(std::vector<git::Remote> &remotes)
{
    return get_impl()->get_remotes(remotes);
}

Result Git::get_branches(git::Branches &branches, git::BranchType branch_type)
{
    return get_impl()->get_branches(branches, branch_type);
}

Result Git::clone(const std::string &url, const std::string &path, const std::string &branch)
{
    set_url(url);
    return get_impl()->clone(url, path, branch);
}

Result Git::checkout(const std::string &branch, bool force)
{
    return get_impl()->checkout(branch, force);
}

Result Git::reset(const git::CommitHash &commit, git::ResetType type)
{
    return get_impl()->reset(commit, type);
}

Result Git::fastforward(const git::CommitHash &commit)
{
    return get_impl()->fastforward(commit);
}

Result Git::get_last_commit(git::CommitHash &commit)
{
    return get_impl()->get_last_commit(commit);
}

Result Git::get_parent_commit(const git::CommitHash &commit, git::CommitHash &parent, int nth_parent)
{
    return get_impl()->get_parent_commit(commit, parent, nth_parent);
}

Result Git::is_dirty(bool &dirty)
{
    return get_impl()->is_dirty(dirty);
}

Result Git::is_detached(bool &detached)
{
    return get_impl()->is_detached(detached);
}

Result Git::get_status(git::RepoStatus &repo_status)
{
    return m_impl->get_status(repo_status);
}

bool Git::is_ssh_agent_running(bool log_once)
{
    if (!s_detect_ssh_agent_done) detect_ssh_agent(log_once);

    return s_ssh_agent_running;
}

void Git::detect_ssh_agent(bool log_once)
{
    if (s_detect_ssh_agent_done) return;

    s_detect_ssh_agent_done = true;
    s_ssh_agent_running = m_impl->is_ssh_agent_running();

    if (s_ssh_agent_running && log_once) info("SSH agent detected");
}

Result Git::merge_analysis(const std::vector<std::string> &refs, git::MergeAnalysisResult &merge_analysis_result,
                        std::vector<git::CommitHash> &commits)
{
    return m_impl->merge_analysis(refs, merge_analysis_result, commits);
}

Result Git::fetch(const std::string &remote)
{
    return m_impl->fetch(remote);
}

bool Git::has_branch(const std::string &name, git::BranchType branch_type)
{
    return m_impl->has_branch(name, branch_type);
}

int Git::get_hash(const std::string &revision, std::string &hash, git::BranchType branch_type)
{
    return m_impl->get_hash(revision, hash, branch_type);
}

Result Git::walk_commits(std::shared_ptr<git::WalkCommit> walk_commit)
{
    return m_impl->walk_commits(walk_commit);
}

Result Git::diff(const git::CommitHash commit_hash, std::shared_ptr<git::Diff> diff)
{
    return m_impl->diff(commit_hash, diff);
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

void Git::set_logger_if(std::shared_ptr<log::Logger_if> logger_if)
{
    get_impl()->set_logger_if(logger_if);
}

} // namespace esys::repo::libgit2
