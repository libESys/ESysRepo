/*!
 * \file esys/repo/githelper.cpp
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
#include "esys/repo/githelper.h"
#include "esys/repo/filesystem.h"

#include <esys/log/consolelockguard.h>

#include <boost/filesystem.hpp>

#include <sstream>
#include <iostream>

namespace esys
{

namespace repo
{

GitHelper::GitHelper(std::shared_ptr<GitBase> git, std::shared_ptr<Logger_if> log_if, int repo_idx)
    : log::User()
    , m_git(git)
    , m_repo_idx(repo_idx)
{
    set_logger_if(log_if);
}

GitHelper::~GitHelper()
{
    if (get_auto_close() && get_git() && get_git()->is_open()) close(log::Level::DEBUG);
}

void GitHelper::debug(int level, const std::string &msg)
{
    std::ostringstream oss;

    init_oss(oss, msg);

    clean_cout();
    log::User::debug(level, oss.str());
    init_oss_clear();
}

void GitHelper::info(const std::string &msg)
{
    std::ostringstream oss;

    init_oss(oss, msg);

    clean_cout();
    log::User::info(oss.str());
    init_oss_clear();
}

void GitHelper::warn(const std::string &msg)
{
    std::ostringstream oss;

    init_oss(oss, msg);

    clean_cout();
    log::User::warn(oss.str());
    init_oss_clear();
}

void GitHelper::error(const std::string &msg)
{
    std::ostringstream oss;

    init_oss(oss, msg);

    clean_cout();
    log::User::error(oss.str());
    init_oss_clear();
}

void GitHelper::critical(const std::string &msg)
{
    std::ostringstream oss;

    init_oss(oss, msg);

    clean_cout();
    log::User::critical(oss.str());
    init_oss_clear();
}

void GitHelper::log(log::Level level, const std::string &msg)
{
    std::ostringstream oss;

    init_oss(oss, msg);

    clean_cout();
    log::User::log(level, oss.str());
    init_oss_clear();
}

void GitHelper::log(const std::string &msg, log::Level level, int debug_level)
{
    std::ostringstream oss;

    init_oss(oss, msg);

    clean_cout();
    log::User::log(oss.str(), level, debug_level);
    init_oss_clear();
}

void GitHelper::error(const std::string &msg, int result)
{
    std::ostringstream oss;

    init_oss(oss, msg);

    clean_cout();
    log::User::error(oss.str(), result);
    init_oss_clear();
}

void GitHelper::done(const std::string &msg, uint64_t elapsed_time)
{
    std::ostringstream oss;

    init_oss(oss, msg);

    oss << " done.\n";
    oss << "    elapsed time (s): " << (elapsed_time / 1000) << "." << (elapsed_time % 1000);
    clean_cout();
    log::User::info(oss.str());
}

int GitHelper::open(const std::string &folder, log::Level log_level, int debug_level)
{
    boost::filesystem::path rel_folder = boost::filesystem::relative(folder);

    std::string msg = "Opening ...\n    path  : " + rel_folder.string();

    log(msg, log_level, debug_level);

    int result = get_git()->open(rel_folder.string());
    if (result < 0) error("Failed with error ", result);
    return result;
}

int GitHelper::clone(const std::string &url, const std::string &path, bool do_close, log::Level log_level,
                     int debug_level)
{
    /*boost::filesystem::path rel_path = boost::filesystem::relative(path);

    std::string msg = "Cloning ...\n    url  : " + url + "\n    path : " + rel_path.string();

    log(msg, log_level, debug_level);

    int result = get_git()->clone(url, path);
    if (result < 0)
        error("Failed with error ", result);
    else
        done("Cloning", get_git()->get_last_cmd_elapsed_time());
    if (!do_close) return result;
    return close(log::Level::DEBUG);*/
    return clone_branch(url, "", path, do_close, log_level, debug_level);
}

int GitHelper::clone_branch(const std::string &url, const std::string &branch, const std::string &path, bool do_close,
                            log::Level log_level, int debug_level)
{
    boost::filesystem::path rel_path = boost::filesystem::relative(path);

    std::string msg = "Cloning ...\n    url  : " + url;
    if (!branch.empty()) msg += "\n    rev  : " + branch;
    msg += "\n    path : " + rel_path.string();

    log(msg, log_level, debug_level);

    int result = get_git()->clone(url, path);
    if (result == 0) done("Cloning", get_git()->get_last_cmd_elapsed_time());
    /*else
        error("Failed with error ", result); */

    if (!do_close) return result;
    return close(log::Level::DEBUG);
}

int GitHelper::clone(const std::string &url, const std::string &temp_path, const std::string &path, bool do_close,
                     log::Level log_level, int debug_level)
{
    auto start_time = std::chrono::steady_clock::now();

    boost::filesystem::path rel_temp_path = boost::filesystem::relative(temp_path);

    if (boost::filesystem::exists(temp_path))
    {
        if (log_level == log::Level::DEBUG)
        {
            std::ostringstream oss;

            init_oss(oss);
            oss << "Remove all: " << rel_temp_path.string();

            int result = log_wrap(boost_no_all::remove_all, log::Level::DEBUG)(oss.str(), temp_path);
            if (result < 0)
            {
                error("Failed to remove all : " + rel_temp_path.string());
                return result;
            }
        }
        else
        {
            int result = boost_no_all::remove_all(temp_path);
            if (result < 0)
            {
                error("Failed to delete path : " + temp_path);
                return result;
            }
        }
    }

    std::string clone_msg;
    boost::filesystem::path rel_path = boost::filesystem::relative(path);

    clone_msg = "Cloning ...\n    url  : " + url + "\n    path : " + rel_path.string();
    log(clone_msg, log::Level::INFO);

    if (log_level == log::Level::DEBUG)
    {
        clone_msg = "Cloning ...\n    url  : " + url + "\n    path : " + rel_temp_path.string();
        log(clone_msg, log::Level::DEBUG);
    }

    int result = get_git()->clone(url, temp_path);
    if (result < 0)
    {
        error("Failed to clone");
        return result;
    }

    if (do_close) close(log::Level::DEBUG);

    if (log_level == log::Level::DEBUG)
    {
        std::ostringstream oss;

        init_oss(oss);
        oss << "Move:\n    src  : " << rel_temp_path.string() << "\n    dest : " << rel_path.string();

        result = log_wrap(boost_no_all::move, log::Level::DEBUG)(oss.str(), temp_path, path, true);
        if (result < 0) return result;
    }
    else
    {
        result = boost_no_all::move(temp_path, path, true);
        if (result == -1)
        {
            error("Failed to copy from temp_path to path : " + temp_path + " -> " + path);
            return result;
        }
        else if (result == -2)
            warn("Failed to delete temp_path : " + temp_path);
    }
    auto stop_time = std::chrono::steady_clock::now();
    auto d_milli = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time).count();

    done("Cloning", static_cast<uint64_t>(d_milli));
    return 0;
}

int GitHelper::close(log::Level log_level, int debug_level)
{
    if (!get_git()->is_open()) return 0;

    log("Closing ...", log_level, debug_level);

    int result = get_git()->close();
    if (result < 0)
        error("Close git repo failed with error ", result);
    else
        log("Closed.", log_level, debug_level);

    return result;
}

int GitHelper::fastforward(const git::Commit &commit, log::Level log_level, int debug_level)
{
    log("Fast forwarding ...", log_level, debug_level);

    int result = get_git()->fastforward(commit);
    if (result < 0)
        error("Failed with error ", result);
    else
        log("Fast forwarded successfully.", log_level, debug_level);

    return result;
}

int GitHelper::fetch(const std::string &remote, log::Level log_level, int debug_level)
{
    log("Fetching ...", log_level, debug_level);

    int result = get_git()->fetch(remote);
    if (result < 0)
        error("Failed with error ", result);
    else
        log("Fetched successfully.", log_level, debug_level);

    return result;
}

int GitHelper::fetch(log::Level log_level, int debug_level)
{
    return fetch("", log_level, debug_level);
}

int GitHelper::get_branches(git::Branches &branches, git::BranchType branch_type, log::Level log_level, int debug_level)
{
    log("Getting branches ...", log::Level::DEBUG);
    int result = get_git()->get_branches(branches, branch_type);
    if (result < 0)
        error("Failed with error ", result);
    else
        log("Got branches.", log::Level::DEBUG);

    return result;
}

bool GitHelper::has_branch(const std::string &name, git::BranchType branch_type, log::Level log_level, int debug_level)
{
    log("Check branch existance " + name + " ...", log::Level::DEBUG);
    bool result = get_git()->has_branch(name, branch_type);
    if (result)
        log("Found it.", log::Level::DEBUG);
    else
        log("Not Found", log::Level::DEBUG);
    return result;
}

int GitHelper::get_hash(const std::string &revision, std::string &hash, log::Level log_level, int debug_level)
{
    log("Check remote hash for " + revision + " ...", log::Level::DEBUG);
    int result = get_git()->get_hash(revision, hash, git::BranchType::REMOTE);
    if (result == 0)
        log("Found it.", log::Level::DEBUG);
    else
        log("Not Found", log::Level::DEBUG);
    return result;
}

int GitHelper::get_hash_local(const std::string &revision, std::string &hash, log::Level log_level, int debug_level)
{
    log("Check local hash for " + revision + " ...", log::Level::DEBUG);
    int result = get_git()->get_hash(revision, hash, git::BranchType::LOCAL);
    if (result)
        log("Found it.", log::Level::DEBUG);
    else
        log("Not Found", log::Level::DEBUG);
    return result;
}

int GitHelper::is_dirty(bool &dirty, log::Level log_level, int debug_level)
{
    int result = get_git()->is_dirty(dirty);
    if (result < 0)
        error("Failed to check there are changes in the git repo.");
    else
    {
        if (dirty)
            log("Dirty git repo", log_level, debug_level);
        else
            log("No changes in the git repo", log_level, debug_level);
    }
    return result;
}

int GitHelper::is_detached(bool &detached, log::Level log_level, int debug_level)
{
    int result = get_git()->is_detached(detached);
    if (result < 0)
        error("Failed to check if the git repo is detached or not.");
    else
    {
        if (detached)
            log("Git repo is detached", log_level, debug_level);
        else
            log("Git repo is not detached", log_level, debug_level);
    }
    return result;
}

int GitHelper::get_status(git::RepoStatus &status, log::Level log_level, int debug_level)
{
    int result = get_git()->get_status(status);
    if (result < 0)
        error("Failed to get the repo status");
    else
        log("Succeeded to get repo status", log_level, debug_level);

    return result;
}

int GitHelper::checkout(const std::string &branch, bool force, log::Level log_level, int debug_level)
{
    int result = get_git()->checkout(branch, force);
    if (result < 0)
        error("Failed to checkout");
    else
        log("Checkout succeeded", log_level, debug_level);
    return result;
}

int GitHelper::merge_analysis(const std::vector<std::string> &refs, git::MergeAnalysisResult &merge_analysis_result,
                              std::vector<git::Commit> &commits, log::Level log_level, int debug_level)
{
    int result = get_git()->merge_analysis(refs, merge_analysis_result, commits);
    if (result < 0)
        error("Merge analysis failed");
    else
        log("Merge analysis succeeded", log_level, debug_level);
    return result;
}

int GitHelper::move(const std::string &src, const std::string &dst, bool recursive, log::Level log_level,
                    int debug_level)
{
    boost::filesystem::path rel_src = boost::filesystem::relative(src);
    boost::filesystem::path rel_dst = boost::filesystem::relative(dst);
    std::ostringstream oss;

    init_oss(oss);
    oss << "Move:\n    src  : " << rel_src.string() << "\n    dest : " << rel_dst.string();

    int result = log_wrap(boost_no_all::move, log_level)(oss.str(), rel_src.string(), rel_dst.string(), true);
    return result;
}

void GitHelper::set_git(std::shared_ptr<GitBase> git)
{
    m_git = git;
}

std::shared_ptr<GitBase> GitHelper::get_git()
{
    return m_git.lock();
}

void GitHelper::set_auto_close(bool auto_close)
{
    m_auto_close = auto_close;
}

bool GitHelper::get_auto_close() const
{
    return m_auto_close;
}

void GitHelper::set_repo_idx(int repo_idx)
{
    m_repo_idx = repo_idx;
}

int GitHelper::get_repo_idx() const
{
    return m_repo_idx;
}

void GitHelper::set_display_repo_idx(bool display_repo_idx)
{
    m_display_repo_idx = display_repo_idx;
}

bool GitHelper::get_display_repo_idx() const
{
    return m_display_repo_idx;
}

void GitHelper::init_oss_done()
{
    m_init_oss_done = true;
}

void GitHelper::init_oss_clear()
{
    m_init_oss_done = false;
}

bool GitHelper::is_init_oss_done()
{
    return m_init_oss_done;
}

void GitHelper::init_oss(std::ostringstream &oss)
{
    if (is_init_oss_done()) return;

    oss.str("");
    if ((get_repo_idx() != -1) && (get_display_repo_idx())) oss << "[" << get_repo_idx() << "] ";
    init_oss_done();
}

void GitHelper::init_oss(std::ostringstream &oss, const std::string &msg)
{
    init_oss(oss);

    oss << msg;
}

void GitHelper::clean_cout()
{
    log::ConsoleLockGuard<log::User> lock(this);

    std::string s = "             ";
    std::cout << "\r";

    for (int idx = 0; idx < 8; ++idx) std::cout << s;
    std::cout << "\r";
}

} // namespace repo

} // namespace esys
