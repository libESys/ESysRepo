/*!
 * \file esys/repo/manifest/syncrepo_manifest.cpp
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
#include "esys/repo/manifest/syncrepo.h"
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

SyncRepo::SyncRepo()
    : log::User()
{
}

SyncRepo::~SyncRepo()
{
}

int SyncRepo::run()
{
    return process_repo();
}

int SyncRepo::process_repo()
{
    boost::filesystem::path path = get_config_folder()->get_parent_path();
    if (get_repo()->get_path() != ".") path /= get_repo()->get_path();

    if (!GitBase::is_repo(path.string())) return clone();
    return fetch_update();
}

int SyncRepo::clone()
{
    GitHelper git_helper(get_git(), get_logger_if(), static_cast<int>(get_repo_idx()));
    int result;
    std::string url = get_repo()->get_location()->get_address();
    url += "/" + get_repo()->get_name();

    bool do_close = true;
    if (!get_repo()->get_revision().empty()) do_close = false;

    boost::filesystem::path path = get_config_folder()->get_parent_path();
    if (get_repo()->get_path() != ".")
    {
        // A simple clone can be made
        path /= get_repo()->get_path();
        result = git_helper.clone(url, path.string(), do_close, log::Level::INFO);
        if (result < 0) return result;

        if (get_repo()->get_revision().empty()) return 0;

        result = git_helper.checkout(get_repo()->get_revision(), false, log::Level::INFO);
        git_helper.close(log::Level::DEBUG);
        return result;
    }

    // Here since the folder where to clone is not empty so a temporary folder is used
    boost::filesystem::path temp_path = get_config_folder()->get_temp_path();
    std::ostringstream oss;
    oss << "repo_temp" << get_repo_idx();
    temp_path /= oss.str();

    result = git_helper.clone(url, temp_path.string(), path.string(), do_close, get_log_level());
    if (result < 0) return result;

    if (get_repo()->get_revision().empty()) return 0;

    result = git_helper.checkout(get_repo()->get_revision(), false, log::Level::INFO);
    git_helper.close(log::Level::DEBUG);
    return result;
}

int SyncRepo::fetch_update()
{
    GitHelper git_helper(get_git(), get_logger_if(), static_cast<int>(get_repo_idx()));
    boost::filesystem::path path = get_config_folder()->get_parent_path();
    if (get_repo()->get_path() != ".") path /= get_repo()->get_path();

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

    GitBase::sort_branches(branches);

    /*result = git_helper.merge_analysis()
    const std::vector<std::string> &refs, git::MergeAnalysisResult &merge_analysis_result,
                       std::vector<git::Commit> &commits */

    return -1;
}

void SyncRepo::set_log_level(log::Level log_level)
{
    m_log_level = log_level;
}

log::Level SyncRepo::get_log_level() const
{
    return m_log_level;
}

void SyncRepo::set_repo_idx(std::size_t repo_idx)
{
    m_repo_idx = repo_idx;
}

std::size_t SyncRepo::get_repo_idx() const
{
    return m_repo_idx;
}

std::size_t &SyncRepo::get_repo_idx()
{
    return m_repo_idx;
}

} // namespace manifest

} // namespace repo

} // namespace esys
