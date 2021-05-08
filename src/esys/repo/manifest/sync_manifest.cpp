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

namespace esys
{

namespace repo
{

namespace manifest
{

Sync::Sync()
    : log::User()
{
}

Sync::~Sync()
{
}

int Sync::run()
{
    if (get_git() == nullptr) return -1;
    if (get_git()->is_open()) return -2;

    int result;
    result = get_git()->open(get_config_folder()->get_manifest_repo_path());
    if (result < 0)
    {
        error("Couldn't open the manifest git repo");
        return -3;
    }
    bool dirty;
    if (get_git()->is_dirty(dirty) < 0) return -4;
    if (dirty)
    {
        warn("Sync manifest aborted: found changes in the git repo.");
        get_git()->close();
        return -5;
    }

    result = get_git()->fetch();
    if (result < 0)
    {
        error("Fetch failed on the manifest git repo");
        get_git()->close();
        return -6;
    }

    bool detached;
    result = get_git()->is_detached(detached);
    if (result < 0)
    {
        error("Couldn't detect if the git repo is detached or not.");
        get_git()->close();
        return -7;
    }

    if (detached)
    {
        warn("Sync manifest aborted: the git repo is detached.");
        get_git()->close();
        return -8;
    }

    git::Branches branches;

    result = get_git()->get_branches(branches);
    if (result < 0)
    {
        get_git()->close();
        return -9;
    }

    if (branches.get_head() == nullptr)
    {
        error("Couldn't get the HEAD.");
        get_git()->close();
        return -10;
    }

    std::vector<std::string> refs;
    git::MergeAnalysisResult merge_analysis_result;
    std::vector<git::Commit> commits;

    refs.push_back(branches.get_head()->get_remote_branch());

    result = get_git()->merge_analysis(refs, merge_analysis_result, commits);
    if (result < 0)
    {
        error("Merge analysis failed.");
        get_git()->close();
        return -11;
    }

    if (merge_analysis_result == git::MergeAnalysisResult::UP_TO_DATE)
    {
        info("Manifest up to date.");
        get_git()->close();
        return 0;
    }
    if (merge_analysis_result != git::MergeAnalysisResult::FASTFORWARD)
    {
        warn("Sync manifest aborted: can't be fastforwarded.");
        get_git()->close();
        return -12;
    }

    // For a fastforward, there should be only one commit
    if (commits.size() != 1)
    {
        error("fastforward failed.");
        get_git()->close();
        return -13;
    }

    info("Fastforward manifest ...");

    result = get_git()->fastforward(commits[0]);
    if (result < 0)
    {
        error("Fastforward failed.");
        get_git()->close();
        return -14;
    }
    info("Fastforward manifest completed.");
    get_git()->close();
    return 0;
}

int Sync::process_repo()
{
    return -1;
}

int Sync::fetch_update()
{
    return -1;
}

void Sync::set_git(std::shared_ptr<GitBase> git)
{
    m_git = git;
}

std::shared_ptr<GitBase> Sync::get_git()
{
    return m_git;
}

const std::shared_ptr<GitBase> Sync::get_git() const
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

const std::shared_ptr<ConfigFolder> Sync::get_config_folder() const
{
    return m_config_folder;
}

void Sync::set_log_level(log::Level log_level)
{
    m_log_level = log_level;
}

log::Level Sync::get_log_level() const
{
    return m_log_level;
}

} // namespace manifest

} // namespace repo

} // namespace esys
