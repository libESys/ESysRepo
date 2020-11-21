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

int SyncRepos::run()
{
    if (get_manifest() == nullptr) return -1;
    if (get_config_folder() == nullptr) return -1;
    if (get_git() == nullptr) return -1;

    int local_result;
    int result = 0;

    set_repo_idx(0);
    for (auto location : get_manifest()->get_locations())
    {
        for (auto repo : location->get_repos())
        {
            local_result = process_repo(repo, get_repo_idx());
            if (local_result < 0)
            {
                --result;
                //! \TODO
            }
            ++get_repo_idx();
        }
    }
    return result;
}

int SyncRepos::process_repo(std::shared_ptr<manifest::Repository> repository, std::size_t repo_idx)
{
    boost::filesystem::path path = get_config_folder()->get_parent_path();
    if (repository->get_path() != ".") path /= repository->get_path();

    if (!GitBase::is_repo(path.string())) return clone(repository, repo_idx);
    return fetch_update(repository, repo_idx);
}

int SyncRepos::clone(std::shared_ptr<manifest::Repository> repository, std::size_t repo_idx)
{
    GitHelper git_helper(get_git(), get_logger_if(), static_cast<int>(repo_idx));
    int result;
    std::string url = repository->get_location()->get_address();
    url += "/" + repository->get_name();

    boost::filesystem::path path = get_config_folder()->get_parent_path();
    if (repository->get_path() != ".")
    {
        // A simple clone can be made
        path /= repository->get_path();
        result = git_helper.clone(url, path.string(), true, log::Level::INFO);
        return result;
    }

    // Here since the folder where to clone is not empty so a temporary folder is used
    boost::filesystem::path temp_path = get_config_folder()->get_temp_path();
    std::ostringstream oss;
    oss << "repo_temp" << repo_idx;
    temp_path /= oss.str();

    result = git_helper.clone(url, temp_path.string(), path.string(), true, get_log_level());
    return result;
}

int SyncRepos::fetch_update(std::shared_ptr<manifest::Repository> repository, std::size_t repo_idx)
{
    GitHelper git_helper(get_git(), get_logger_if(), static_cast<int>(repo_idx));
    boost::filesystem::path path = get_config_folder()->get_parent_path();
    if (repository->get_path() != ".") path /= repository->get_path();

    int result = git_helper.open(path.string(), log::Level::INFO);
    if (result < 0) return result;

    bool dirty = false;
    result = git_helper.is_dirty(dirty, log::Level::DEBUG);
    if (result < 0) return result;

    if (dirty)
    {
        git_helper.info("Changes detected in repo, no sync.");
        return 0;
    }

    std::vector<git::Branch> branches;
    result = git_helper.get_branches(branches, git::BranchType::LOCAL, log::Level::DEBUG);
    if (result < 0)
    {
        error("Couldn't get the list of local branches");
        return -1;
    }

    GitHelper::sort_branches(branches);



    return -1;
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

} // namespace manifest

} // namespace repo

} // namespace esys
