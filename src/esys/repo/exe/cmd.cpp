/*!
 * \file esys/repo/exe/cmd.cpp
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
#include "esys/repo/exe/cmd.h"
#include "esys/repo/filesystem.h"
#include "esys/repo/configfolder.h"
#include "esys/repo/gitmngr.h"

#include <esys/log/consolelockguard.h>

#include <boost/filesystem.hpp>

#include <sstream>
#include <iostream>

namespace esys
{

namespace repo
{

namespace exe
{

Cmd::Cmd(const std::string &name)
    : log::User()
    , m_name(name)
{
}

Cmd::~Cmd() = default;

const std::string &Cmd::get_name() const
{
    return m_name;
}

void Cmd::set_job_count(int job_count)
{
    m_job_count = job_count;
}

int Cmd::get_job_count() const
{
    return m_job_count;
}

int Cmd::run()
{
    m_start_time = std::chrono::steady_clock::now();

    std::string msg = get_name() + " ...";
    info(msg);

    if (get_git() == nullptr) set_git(GitMngr::new_ptr());
    if (get_logger_if() != nullptr) get_git()->set_logger_if(get_logger_if());

    int result = impl_run();

    auto stop_time = std::chrono::steady_clock::now();
    auto d_milli = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - m_start_time).count();

    std::ostringstream oss;
    msg = get_name();
    oss << "    elapsed time (s): " << (d_milli / 1000) << "." << (d_milli % 1000);
    if (result == 0)
    {
        msg += " done.\n";
        msg += oss.str();
        info(msg);
    }
    else
    {
        msg += " failed.\n";
        msg += oss.str();
        error(msg);
    }
    return result;
}

void Cmd::set_manifest(std::shared_ptr<Manifest> manifest)
{
    m_manifest = manifest;
}

std::shared_ptr<Manifest> Cmd::get_manifest()
{
    return m_manifest;
}

const std::shared_ptr<Manifest> Cmd::get_manifest() const
{
    return m_manifest;
}

void Cmd::set_git(std::shared_ptr<GitBase> git)
{
    m_git = git;
}

std::shared_ptr<GitBase> Cmd::get_git()
{
    return m_git;
}

const std::shared_ptr<GitBase> Cmd::get_git() const
{
    return m_git;
}

void Cmd::set_workspace_path(const std::string &workspace_path)
{
    m_workspace_path = workspace_path;
}

const std::string &Cmd::get_workspace_path() const
{
    return m_workspace_path;
}

std::string Cmd::find_workspace_path(const std::string &path)
{
    boost::filesystem::path cur_path;

    if (!path.empty())
        cur_path = path;
    else
        cur_path = boost::filesystem::current_path();

    while (!cur_path.empty())
    {
        if (ConfigFolder::is_config_folder(cur_path.string())) return cur_path.string();
        cur_path = cur_path.parent_path();
    }

    return "";
}

std::string Cmd::find_git_repo_path(const std::string &path)
{
    boost::filesystem::path cur_path;

    if (!path.empty())
        cur_path = path;
    else
        cur_path = boost::filesystem::current_path();

    while (!cur_path.empty())
    {
        if (GitBase::is_repo(cur_path.string())) return cur_path.string();
        cur_path = cur_path.parent_path();
    }

    return "";
}

void Cmd::set_debug(bool debug)
{
    m_debug = debug;
}

bool Cmd::get_debug() const
{
    return m_debug;
}

int Cmd::set_folder(const std::string &folder)
{
    boost::filesystem::path path = Cmd::find_workspace_path(folder);
    if (path.empty()) return -1;

    set_workspace_path(path.string());
   
    return 0;
}

void Cmd::set_sub_args(const std::vector<std::string> &sub_args)
{
    m_sub_args = sub_args;
}

const std::vector<std::string> &Cmd::get_sub_args() const
{
    return m_sub_args;
}

void Cmd::set_time(bool time)
{
    m_time = time;
}

bool Cmd::get_time() const
{
    return m_time;
}

void Cmd::set_delta_time(bool delta_time)
{
    m_delta_time = delta_time;
}

bool Cmd::get_delta_time() const
{
    return m_delta_time;
}

void Cmd::set_groups(const std::vector<std::string> &groups)
{
    m_groups = groups;
}

const std::vector<std::string> &Cmd::get_groups() const
{
    return m_groups;
}

int Cmd::process_sub_args_as_git_repo_path(const std::string &input_path)
{
    if (input_path.empty()) return 0;

    boost::filesystem::path the_input_path = input_path;
    if (the_input_path == ".") the_input_path = boost::filesystem::current_path();

    boost::filesystem::path git_repo = Cmd::find_git_repo_path(the_input_path.string());
    boost::filesystem::path workspace_path = get_workspace_path();

    if (workspace_path.empty())
    {
        workspace_path = Cmd::find_workspace_path(the_input_path.string());

        if (workspace_path.empty())
        {
            error("Requires ESysRepo to be installed first.");
            return -1;
        }
        else
            set_workspace_path(workspace_path.string());
    }

    if (git_repo.empty()) return 0;

    if (!boost::filesystem::exists(the_input_path))
    {
        // The input path doesn't exist
        // Couldn't it be the relative path of a git repo in the manifest?
        auto repo = get_manifest()->find_repo_by_path(the_input_path.string());
        if (repo == nullptr)
        {
            error("The given path doesn't exists : " + the_input_path.string());
            return -1;
        }

        // This was indeed the relative path of a git repo in the manifest
        git_repo = the_input_path.string();
    }
    else
    {
        // We need to find which repo this is related too
        boost::filesystem::path git_rel_path = boost::filesystem::relative(git_repo, workspace_path);

        if (git_rel_path.empty())
        {
            error("The following git repo doesn't seem to be known by ESysRepo: " + git_repo.string());
            return -1;
        }
        git_repo = git_rel_path;
    }
    m_input_rel_git_repo_paths.push_back(git_repo.generic().string());
    return 0;
}

int Cmd::process_sub_args_as_git_repo_paths()
{
    if (get_manifest() == nullptr) return -1;

    int result = 0;
    int local_result;

    for (auto &input_path : get_sub_args())
    {
        local_result = process_sub_args_as_git_repo_path(input_path);
        if (local_result < 0) --result;
    }
    return result;
}

const std::vector<std::string> &Cmd::get_input_git_repo_paths() const
{
    return m_input_rel_git_repo_paths;
}

void Cmd::set_config_folder(std::shared_ptr<ConfigFolder> config_folder)
{
    m_config_folder = config_folder;
}

std::shared_ptr<ConfigFolder> Cmd::get_config_folder()
{
    return m_config_folder;
}

const std::shared_ptr<ConfigFolder> Cmd::get_config_folder() const
{
    return m_config_folder;
}

void Cmd::set_loader(std::shared_ptr<manifest::Loader> loader)
{
    m_loader = loader;
}

std::shared_ptr<manifest::Loader> Cmd::get_loader()
{
    return m_loader;
}

const std::shared_ptr<manifest::Loader> Cmd::get_loader() const
{
    return m_loader;
}

int Cmd::open_esysrepo_folder()
{
    auto config_folder = std::make_shared<ConfigFolder>();

    set_config_folder(config_folder);

    boost::filesystem::path rel_parent_path = boost::filesystem::relative(get_workspace_path());
    int result = config_folder->open(get_workspace_path());
    if (result < 0)
        error("Failed to open esysrepo folder : " + rel_parent_path.string());
    else
        debug(0, "Opened esysrepo folder : " + rel_parent_path.string());

    return result;
}

int Cmd::load_manifest()
{
    if (get_config_folder() == nullptr) return -1;

    if (get_loader() == nullptr) set_loader(std::make_shared<manifest::Loader>());
    if (get_manifest() == nullptr) set_manifest(std::make_shared<Manifest>());
    get_manifest()->clear();

    get_loader()->set_manifest(get_manifest());
    get_loader()->set_config_folder(get_config_folder());

    get_loader()->set_logger_if(get_logger_if());
    int result = get_loader()->run();
    return result;
}

std::string Cmd::get_extra_start_msg()
{
    return "";
}

void Cmd::debug(int level, const std::string &msg)
{
    clean_cout();

    User::debug(level, msg);
}

void Cmd::info(const std::string &msg)
{
    clean_cout();

    User::info(msg);
}

void Cmd::warn(const std::string &msg)
{
    clean_cout();

    User::warn(msg);
}

void Cmd::error(const std::string &msg)
{
    clean_cout();

    User::error(msg);
}

void Cmd::critical(const std::string &msg)
{
    clean_cout();

    User::critical(msg);
}

void Cmd::log(log::Level level, const std::string &msg)
{
    clean_cout();

    User::log(level, msg);
}

void Cmd::log(const std::string &msg, log::Level level, int debug_level)
{
    clean_cout();

    User::log(msg, level, debug_level);
}

void Cmd::clean_cout()
{
    /*log::ConsoleLockGuard<log::User> lock(this);

    std::string s = "             ";
    std::cout << "\r";

    for (int idx = 0; idx < 8; ++idx)
        std::cout << s;
    std::cout << "\r"; */
}

} // namespace exe

} // namespace repo

} // namespace esys
