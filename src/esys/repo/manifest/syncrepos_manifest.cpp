/*!
 * \file esys/repo/manifest/syncrepos_manifest.cpp
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
#include "esys/repo/manifest/syncrepos.h"
#include "esys/repo/manifest/location.h"
#include "esys/repo/git.h"
#include "esys/repo/githelper.h"

#include "esys/repo/filesystem.h"

#include <boost/filesystem.hpp>

#include <sstream>

namespace esys
{

namespace repo
{

namespace manifest
{

SyncRepos::SyncRepos()
    : log::User()
{
}

SyncRepos::~SyncRepos()
{
}

void SyncRepos::set_manifest(std::shared_ptr<Manifest> manifest)
{
    m_manifest = manifest;
}

std::shared_ptr<Manifest> SyncRepos::get_manifest()
{
    return m_manifest;
}

const std::shared_ptr<Manifest> SyncRepos::get_manifest() const
{
    return m_manifest;
}

void SyncRepos::set_config_folder(std::shared_ptr<ConfigFolder> config_folder)
{
    m_config_folder = config_folder;
}

std::shared_ptr<ConfigFolder> SyncRepos::get_config_folder()
{
    return m_config_folder;
}

const std::shared_ptr<ConfigFolder> SyncRepos::get_config_folder() const
{
    return m_config_folder;
}

void SyncRepos::set_git(std::shared_ptr<GitBase> git)
{
    m_git = git;
}

std::shared_ptr<GitBase> SyncRepos::get_git()
{
    return m_git;
}

const std::shared_ptr<GitBase> SyncRepos::get_git() const
{
    return m_git;
}

std::shared_ptr<GitBase> SyncRepos::get_git_or_new()
{
    if (get_git() != nullptr) return get_git();

    return new_git();
}

void SyncRepos::set_git_generator(GitBase::GeneratorType git_generator)
{
    m_git_generator = git_generator;
}

GitBase::GeneratorType SyncRepos::get_git_generator()
{
    return m_git_generator;
}

std::shared_ptr<GitBase> SyncRepos::new_git()
{
    if (get_git_generator() != nullptr) return get_git_generator()();

    return Git::new_ptr();
}

int SyncRepos::run()
{
    if (get_manifest() == nullptr) return -1;
    if (get_config_folder() == nullptr) return -1;
    if (get_git() == nullptr) return -1;

    int result = 0;

    set_repo_idx(0);
    for (auto location : get_manifest()->get_locations())
    {
        for (auto repo : location->get_repos())
        {
            std::shared_ptr<SyncRepo> sync_repo = std::make_shared<SyncRepo>();

            sync_repo->set_repo(repo);
            sync_repo->set_repo_idx(get_repo_idx());
            sync_repo->set_config_folder(get_config_folder());
            sync_repo->set_git(new_git());
            sync_repo->get_git()->set_logger_if(get_logger_if());
            sync_repo->set_logger_if(get_logger_if());
            
            get_run_tasks().add(sync_repo);

            ++get_repo_idx();
        }
    }
    return get_run_tasks().run();
}

void SyncRepos::set_log_level(log::Level log_level)
{
    m_log_level = log_level;
}

log::Level SyncRepos::get_log_level() const
{
    return m_log_level;
}

void SyncRepos::set_repo_idx(std::size_t repo_idx)
{
    m_repo_idx = repo_idx;
}

std::size_t SyncRepos::get_repo_idx() const
{
    return m_repo_idx;
}

std::size_t &SyncRepos::get_repo_idx()
{
    return m_repo_idx;
}

void SyncRepos::set_job_count(int job_count)
{
    m_run_tasks.set_job_count(job_count);
}

int SyncRepos::get_job_count() const
{
    return m_run_tasks.get_job_count();
}

RunTasks &SyncRepos::get_run_tasks()
{
    return m_run_tasks;
}

const RunTasks &SyncRepos::get_run_tasks() const
{
    return m_run_tasks;
}

} // namespace manifest

} // namespace repo

} // namespace esys
