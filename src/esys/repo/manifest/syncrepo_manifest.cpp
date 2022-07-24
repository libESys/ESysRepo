/*!
 * \file esys/repo/manifest/syncrepo_manifest.cpp
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
#include "esys/repo/manifest/syncrepo.h"
#include "esys/repo/manifest/location.h"

#include "esys/repo/filesystem.h"

#include <boost/filesystem.hpp>

#include <sstream>

namespace esys::repo::manifest
{

SyncRepo::SyncRepo()
    : log::User()
{
}

SyncRepo::~SyncRepo() = default;

int SyncRepo::run()
{
    return process_repo();
}

int SyncRepo::process_repo()
{
    boost::filesystem::path path = get_config_folder()->get_workspace_path();
    if (get_repo()->get_path() != ".") path /= get_repo()->get_path();

    if (!GitBase::is_repo(path.string())) return clone();
    return fetch_update();
}

bool SyncRepo::has_branch(GitHelper &git_helper, const std::string &branch)
{
    git::Branches branches;
    int result = git_helper.get_branches(branches, git::BranchType::REMOTE, log::Level::DEBUG);
    if (result < 0)
    {
        git_helper.error("Couldn't get the list of local branches");
        return false;
    }

    branches.sort();

    auto branch_ptr = branches.find(branch);

    if (branch_ptr != nullptr)
    {
        git_helper.debug(0, "Branch found : " + branch);
        return true;
    }
    git_helper.debug(0, "Branch not found : " + branch);
    return false;
}

std::string SyncRepo::get_checkout_revision(GitHelper &git_helper)
{
    if (get_branch().empty()) return get_repo()->get_revision();

    bool branch_exists = git_helper.has_branch(get_branch(), git::BranchType::REMOTE, esys::log::Level::DEBUG);
    if (branch_exists) return get_branch();
    return get_repo()->get_revision();
}

std::shared_ptr<GitHelper> SyncRepo::new_git_helper()
{
    auto git_helper = std::make_shared<GitHelper>(get_git(), get_logger_if(), static_cast<int>(get_repo_idx()));

    get_git()->set_logger_if(git_helper);
    return git_helper;
}

int SyncRepo::clone()
{
    std::shared_ptr<GitHelper> git_helper = new_git_helper();
    std::string url = get_repo_url();
    int result = 0;
    std::string branch_to_checkout;

    boost::filesystem::path path = get_config_folder()->get_workspace_path();
    if (get_repo()->get_path() != ".")
    {
        // A simple clone can be made
        path /= get_repo()->get_path();
        Result rresult = git_helper->clone(url, path.string(), false, log::Level::INFO);
        if (rresult.error())
        {
            git_helper->close(log::Level::DEBUG);
            return rresult.get_result_code_int();
        }

        if (!get_branch().empty())
        {
            result = git_helper->fetch(get_log_level());
            if (result < 0)
            {
                git_helper->close(log::Level::DEBUG);
                return result;
            }
        }

        branch_to_checkout = get_checkout_revision(*git_helper.get());
        git_helper->debug(0, "branch_to_checkout = " + branch_to_checkout);
        if (branch_to_checkout.empty()) return 0;

        result = git_helper->checkout(branch_to_checkout, false, log::Level::INFO);
        git_helper->close(log::Level::DEBUG);
        return result;
    }

    // Here since the folder where to clone is not empty so a temporary folder is used
    boost::filesystem::path temp_path = get_config_folder()->get_temp_path();
    std::ostringstream oss;
    oss << "repo_temp" << get_repo_idx();
    temp_path /= oss.str();

    result = git_helper->clone(url, temp_path.string(), path.string(), true, get_log_level());
    if (result < 0)
    {
        git_helper->close(log::Level::DEBUG);
        return result;
    }

    Result rresult = git_helper->open(path.string(), esys::log::INFO);
    if (rresult.error())
    {
        return rresult.get_result_code_int();
    }

    if (!get_branch().empty())
    {
        result = git_helper->fetch(get_log_level());
        if (result < 0)
        {
            git_helper->close(log::Level::DEBUG);
            return result;
        }
    }

    branch_to_checkout = get_checkout_revision(*git_helper.get());
    git_helper->debug(0, "branch_to_checkout = " + branch_to_checkout);
    if (branch_to_checkout.empty()) return 0;

    result = git_helper->checkout(branch_to_checkout, get_force(), log::Level::INFO);
    git_helper->close(log::Level::DEBUG);

    return result;
}

int SyncRepo::fetch_update()
{
    std::shared_ptr<GitHelper> git_helper = new_git_helper();
    git_helper->set_display_repo_idx(get_display_repo_idx());

    boost::filesystem::path path = get_config_folder()->get_workspace_path();
    if (get_repo()->get_path() != ".") path /= get_repo()->get_path();

    Result rresult = git_helper->open(path.string(), log::Level::INFO);
    if (rresult.error()) return rresult.get_result_code_int();

    bool dirty = false;
    int result = git_helper->is_dirty(dirty, log::Level::DEBUG);
    if (result < 0) return result;

    if (dirty)
    {
        git_helper->warn("Changes detected in repo, no sync.");
        return 0;
    }

    if (get_branch().empty())
        return normal_sync(*git_helper.get());
    else
        return branch_sync(*git_helper.get());
}

int SyncRepo::normal_sync(GitHelper &git_helper)
{
    bool detached = false;
    int result = git_helper.is_detached(detached, log::Level::DEBUG);
    if (result < 0)
    {
        git_helper.error("Couldn't detect if the git repo is detached or not.");
        return -1;
    }

    if (detached)
    {
        git_helper.warn("Sync repo aborted: the git repo is detached.");
        return -2;
    }

    result = git_helper.fetch(log::Level::DEBUG);
    if (result < 0)
    {
        git_helper.error("Fetch failed on the git repo");
        return -3;
    }

    git::Branches branches;
    result = git_helper.get_branches(branches, git::BranchType::LOCAL, log::Level::DEBUG);
    if (result < 0)
    {
        git_helper.error("Couldn't get the list of local branches");
        return -3;
    }

    branches.sort();

    if (branches.get_head() == nullptr)
    {
        git_helper.error("Couldn't get the HEAD.");
        return -4;
    }

    std::vector<std::string> refs;
    git::MergeAnalysisResult merge_analysis_result;
    std::vector<git::CommitHash> commits;

    refs.push_back(branches.get_head()->get_remote_branch());

    result = git_helper.merge_analysis(refs, merge_analysis_result, commits, log::Level::DEBUG);
    if (result < 0)
    {
        git_helper.error("Merge analysis failed.");
        return -5;
    }

    if (merge_analysis_result == git::MergeAnalysisResult::UP_TO_DATE)
    {
        git_helper.info("Git repo up to date.");
        return 0;
    }
    if (merge_analysis_result != git::MergeAnalysisResult::FASTFORWARD)
    {
        git_helper.warn("Sync manifest aborted: can't be fastforwarded.");
        return -6;
    }

    // For a fastforward, there should be only one commit
    if (commits.size() != 1)
    {
        git_helper.error("Fast forward failed.");
        return -7;
    }

    git_helper.info("Fast forwarding git repo ...");

    result = git_helper.fastforward(commits[0], log::Level::DEBUG);
    if (result < 0)
    {
        git_helper.error("Fast forward failed.");
        return -8;
    }
    git_helper.info("Fast forward completed.");
    return 0;
}

int SyncRepo::branch_sync(GitHelper &git_helper)
{
    if (!has_branch(git_helper, get_branch())) return normal_sync(git_helper);

    int result = git_helper.checkout(get_branch(), get_force(), log::Level::DEBUG);
    if (result == 0)
        info("Checkout branch " + get_branch() + ".");
    else
        error("Failed to checkout branch " + get_branch() + ".");
    return result;
}

void SyncRepo::set_log_level(log::Level log_level)
{
    m_log_level = log_level;
}

log::Level SyncRepo::get_log_level()
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

void SyncRepo::set_display_repo_idx(bool display_repo_idx)
{
    m_display_repo_idx = display_repo_idx;
}

bool SyncRepo::get_display_repo_idx() const
{
    return m_display_repo_idx;
}

std::string SyncRepo::get_repo_url()
{
    assert(get_repo() != nullptr);
    assert(get_repo()->get_location() != nullptr);

    std::string url;
    if (!get_alt_address())
        url = get_repo()->get_location()->get_address();
    else
        url = get_repo()->get_location()->get_alt_address();

    url += "/" + get_repo()->get_name();

    return url;
}

void SyncRepo::set_branch(const std::string &branch)
{
    m_branch = branch;
}

const std::string &SyncRepo::get_branch() const
{
    return m_branch;
}

void SyncRepo::set_alt_address(bool alt_address)
{
    m_alt_address = alt_address;
}

bool SyncRepo::get_alt_address() const
{
    return m_alt_address;
}

void SyncRepo::set_force(bool force)
{
    m_force = force;
}

bool SyncRepo::get_force() const
{
    return m_force;
}

} // namespace esys::repo::manifest
