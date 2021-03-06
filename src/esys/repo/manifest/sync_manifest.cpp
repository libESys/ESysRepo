/*!
 * \file esys/repo/manifest/sync_manifest.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2021 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/manifest/sync.h"

namespace esys::repo::manifest
{

Sync::Sync()
    : log::User()
{
}

Sync::~Sync() = default;

void Sync::set_branch(const std::string &branch)
{
    m_branch = branch;
}

const std::string &Sync::get_branch() const
{
    return m_branch;
}

void Sync::set_force(bool force)
{
    m_force = force;
}

bool Sync::get_force() const
{
    return m_force;
}

int Sync::is_manifest_modified(bool &modified)
{
    bool dirty = false;
    modified = false;

    if (get_git()->is_dirty(dirty).error()) return GIT_IS_DIRTY_FAILED;

    if (!dirty) return 0;

    git::RepoStatus status;

    Result result = get_git()->get_status(status);
    if (result.error()) return GIT_GET_STATUS_FAILED;

    if (get_config_folder() == nullptr) return CONFIG_FOLDER_IS_NULL;
    auto config = get_config_folder()->get_config();
    if (config == nullptr) return CONFIG_IS_NULL;

    auto rel_file_name = get_config_folder()->get_manifest_rel_file_name();

    auto file_status_it = status.get_map_file_status().find(rel_file_name);
    if (file_status_it == status.get_map_file_status().end()) return 0;

    auto file_status = file_status_it->second;

    warn("The manifest file has local changes!");
    return 0;
}

Result Sync::run()
{
    if (get_git() == nullptr) return ESYSREPO_RESULT(ResultCode::CMD_GIT_IS_NULLPTR);
    if (get_git()->is_open()) return ESYSREPO_RESULT(ResultCode::CMD_GIT_IS_NOT_OPENED);

    Result result = get_git()->open(get_config_folder()->get_manifest_repo_path());
    if (result.error())
    {
        std::string err_str = "Couldn't open the manifest git repo";
        error(err_str);
        return ESYSREPO_RESULT(ResultCode::CMD_GIT_OPEN_FAILED, err_str);
    }
    bool dirty = false;
    if (get_git()->is_dirty(dirty).error()) return ESYSREPO_RESULT(ResultCode::CMD_GIT_IS_DIRTY_FAILED);
    if (dirty)
    {
        std::string err_str = "Sync manifest aborted: found changes in the git repo.";
        warn(err_str);
        get_git()->close();
        return ESYSREPO_RESULT(ResultCode::CMDSYNC_ABORTED_FOUND_CHANGES, err_str);
    }

    result = get_git()->fetch();
    if (result.error())
    {
        std::string err_str = "Fetch failed on the manifest git repo";
        error(err_str);
        get_git()->close();
        return ESYSREPO_RESULT(ResultCode::CMD_GIT_FETCH_FAILED, err_str);
    }

    if (get_branch().empty()) return normal_sync();
    return branch_sync();
}

Result Sync::normal_sync()
{
    bool detached = false;
    Result result = get_git()->is_detached(detached);
    if (result.error())
    {
        error("Couldn't detect if the git repo is detached or not.");
        get_git()->close();
        return ESYSREPO_RESULT(ResultCode::OK);
    }

    if (detached)
    {
        warn("Sync manifest aborted: the git repo is detached.");
        get_git()->close();
        return ESYSREPO_RESULT(ResultCode::OK);
    }

    git::Branches branches;

    result = get_git()->get_branches(branches);
    if (result.error())
    {
        get_git()->close();
        return ESYSREPO_RESULT(result);
    }

    if (branches.get_head() == nullptr)
    {
        std::string err_str = "Couldn't get the HEAD.";
        error(err_str);
        get_git()->close();
        return ESYSREPO_RESULT(ResultCode::CMD_GIT_GET_HEAD_FAILED, err_str);
    }

    std::vector<std::string> refs;
    git::MergeAnalysisResult merge_analysis_result;
    std::vector<git::CommitHash> commits;

    refs.push_back(branches.get_head()->get_remote_branch());

    result = get_git()->merge_analysis(refs, merge_analysis_result, commits);
    if (result.error())
    {
        std::string err_str = "Merge analysis failed.";
        error(err_str);
        get_git()->close();
        return ESYSREPO_RESULT(result, err_str);
    }

    if (merge_analysis_result == git::MergeAnalysisResult::UP_TO_DATE)
    {
        info("Manifest up to date.");
        get_git()->close();
        return ESYSREPO_RESULT(ResultCode::OK);
    }
    if (merge_analysis_result != git::MergeAnalysisResult::FASTFORWARD)
    {
        std::string err_str = "Sync manifest aborted: can't be fastforwarded.";
        warn(err_str);
        get_git()->close();
        return ESYSREPO_RESULT(ResultCode::CMDSYNC_GIT_CAN_NOT_BE_FAST_FORWARDED, err_str);
    }

    // For a fastforward, there should be only one commit
    if (commits.size() != 1)
    {
        std::string err_str = "fastforward failed.";
        error(err_str);
        get_git()->close();
        return ESYSREPO_RESULT(ResultCode::CMD_GIT_MORE_THAN_ONE_COMMIT, err_str);
    }

    info("Fastforward manifest ...");

    result = get_git()->fastforward(commits[0]);
    if (result.error())
    {
        std::string err_str = "Fastforward failed.";
        error(err_str);
        get_git()->close();
        return ESYSREPO_RESULT(result, err_str);
    }
    info("Fastforward manifest completed.");
    get_git()->close();

    return ESYSREPO_RESULT(ResultCode::OK);
}

Result Sync::branch_sync()
{
    Result result = get_git()->fetch();
    if (result.error())
    {
        get_git()->close();
        return ESYSREPO_RESULT(result);
    }

    bool has_branch = get_git()->has_branch(get_branch());

    if (!has_branch) return normal_sync();

    result = get_git()->checkout(get_branch(), get_force());
    if (result.ok())
        info("Manifest: checkout branch " + get_branch() + ".");
    else
        error("Manifest: failed to checkout branch " + get_branch() + ".");
    get_git()->close();
    return ESYSREPO_RESULT(result);
}

int Sync::process_repo()
{
    return NOT_IMPLEMENTED;
}

int Sync::fetch_update()
{
    return NOT_IMPLEMENTED;
}

void Sync::set_git(std::shared_ptr<GitBase> git)
{
    m_git = git;
}

std::shared_ptr<GitBase> Sync::get_git() const
{
    return m_git;
}

void Sync::set_config_folder(std::shared_ptr<ConfigFolder> config_folder)
{
    m_config_folder = config_folder;
}

std::shared_ptr<ConfigFolder> Sync::get_config_folder()
{
    return m_config_folder;
}

void Sync::set_log_level(log::Level log_level)
{
    m_log_level = log_level;
}

log::Level Sync::get_log_level()
{
    return m_log_level;
}

} // namespace esys::repo::manifest
