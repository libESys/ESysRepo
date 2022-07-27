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

namespace esys::repo::exe
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

Result Cmd::run()
{
    m_start_time = std::chrono::steady_clock::now();

    if (get_print_cmd_name_by_base()) print_cmd_name();

    if (get_git() == nullptr) set_git(GitMngr::new_ptr());
    if (get_logger_if() != nullptr) get_git()->set_logger_if(get_logger_if());

    Result result = impl_run();

    auto stop_time = std::chrono::steady_clock::now();
    auto d_milli = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - m_start_time).count();

    std::ostringstream oss;
    std::string msg;

    msg = get_name();
    oss << "    elapsed time (s): " << (d_milli / THOUSAND) << "." << (d_milli % THOUSAND);
    if (result.ok())
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
    return ESYSREPO_RESULT(result);
}

void Cmd::set_manifest(std::shared_ptr<Manifest> manifest)
{
    m_manifest = manifest;
}

std::shared_ptr<Manifest> Cmd::get_manifest() const
{
    return m_manifest;
}

void Cmd::set_git(std::shared_ptr<GitBase> git)
{
    m_git = git;
}

std::shared_ptr<GitBase> Cmd::get_git() const
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

void Cmd::set_folder(const std::string &folder)
{
    m_folder = folder;

    /*boost::filesystem::path path = Cmd::find_workspace_path(folder);
    if (path.empty()) return -1;

    set_workspace_path(path.string());*/
}

const std::string &Cmd::get_folder() const
{
    return m_folder;
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

void Cmd::set_cli_cmd(cli::Cmd *cli_cmd)
{
    m_cli_cmd = cli_cmd;
}

cli::Cmd *Cmd::get_cli_cmd()
{
    return m_cli_cmd;
}

void Cmd::set_app_base(cli::AppBase *app_base)
{
    m_app_base = app_base;
}

cli::AppBase *Cmd::get_app_base()
{
    return m_app_base;
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

Result Cmd::process_sub_args_as_git_repo_paths()
{
    if (get_manifest() == nullptr) return ESYSREPO_RESULT(ResultCode::MANIFEST_IS_NULLPTR);

    int result = 0;

    for (auto &input_path : get_sub_args())
    {
        int local_result = process_sub_args_as_git_repo_path(input_path);
        if (local_result < 0) --result;
    }
    if (result < 0)
        return ESYSREPO_RESULT(ResultCode::CMD_GENERIC_RAW_ERROR, result);
    else
        return ESYSREPO_RESULT(ResultCode::OK);
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

void Cmd::set_loader(std::shared_ptr<manifest::Loader> loader)
{
    m_loader = loader;
}

std::shared_ptr<manifest::Loader> Cmd::get_loader()
{
    return m_loader;
}

Result Cmd::open_esysrepo_folder()
{
    auto config_folder = std::make_shared<ConfigFolder>();

    set_config_folder(config_folder);

    boost::filesystem::path rel_parent_path = boost::filesystem::relative(get_workspace_path());
    Result result = config_folder->open(get_workspace_path());
    if (result.error())
        error("Failed to open esysrepo folder : " + rel_parent_path.string());
    else
        debug(0, "Opened esysrepo folder : " + rel_parent_path.string());

    return ESYSREPO_RESULT(result);
}

Result Cmd::load_manifest()
{
    if (get_config_folder() == nullptr) return ESYSREPO_RESULT(ResultCode::CMD_CONFIG_FOLDER_NULLPTR);

    if (get_loader() == nullptr) set_loader(std::make_shared<manifest::Loader>());
    if (get_manifest() == nullptr) set_manifest(std::make_shared<Manifest>());
    get_manifest()->clear();

    get_loader()->set_manifest(get_manifest());
    get_loader()->set_config_folder(get_config_folder());

    get_loader()->set_logger_if(get_logger_if());
    Result result = get_loader()->run();
    return ESYSREPO_RESULT(result);
}

Result Cmd::default_handling_folder_workspace()
{
    if (!get_folder().empty() && get_workspace_path().empty())
    {
        boost::filesystem::path path = exe::Cmd::find_workspace_path(get_folder());
        if (path.empty())
        {
            std::string err_str = "Couldn't find a folder with ESysRepo from : " + get_folder();
            error(err_str);
            return ESYSREPO_RESULT(ResultCode::CMD_NO_ESYSREPO_FOLDER_FOUND, err_str);
        }
        path = boost::filesystem::absolute(path).normalize().make_preferred();
        set_workspace_path(path.string());
    }
    else if (!get_workspace_path().empty())
    {
        boost::filesystem::path path = exe::Cmd::find_workspace_path(get_workspace_path());
        if (path.empty())
        {
            std::string err_str = "Couldn't find a folder with ESysRepo from : " + get_workspace_path();
            error(err_str);
            return ESYSREPO_RESULT(ResultCode::CMD_NO_ESYSREPO_FOLDER_FOUND, err_str);
        }
        path = boost::filesystem::absolute(path).normalize().make_preferred();
        set_workspace_path(path.string());
    }
    else
    {
        boost::filesystem::path path = exe::Cmd::find_workspace_path();
        if (path.empty())
        {
            std::string err_str =
                "Couldn't find a folder with ESysRepo from : " + boost::filesystem::current_path().string();
            error(err_str);
            return ESYSREPO_RESULT(ResultCode::CMD_NO_ESYSREPO_FOLDER_FOUND, err_str);
        }
        path = boost::filesystem::absolute(path).normalize().make_preferred();
        set_workspace_path(path.string());
    }
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result Cmd::only_one_folder_or_workspace()
{
    if (!get_folder().empty() && !get_workspace_path().empty())
    {
        std::string err_str = "--folder and --workspace can't be specified at the same time";
        error(err_str);
        return ESYSREPO_RESULT(ResultCode::CMD_INCORRECT_PARAMETERS_COMBINATION, err_str);
    }
    else if (!get_folder().empty() || !get_workspace_path().empty())
    {
        boost::filesystem::path path;
        if (!get_folder().empty())
            path = get_folder();
        else
            path = get_workspace_path();
        path = boost::filesystem::absolute(path).normalize().make_preferred();
        set_workspace_path(path.string());
    }
    else
        set_workspace_path(boost::filesystem::current_path().normalize().make_preferred().string());
    return ESYSREPO_RESULT(ResultCode::OK);
}

std::string Cmd::get_extra_start_msg()
{
    return "";
}

void Cmd::set_console_os(std::ostream *console_os)
{
    m_console_os = console_os;
}

std::ostream *Cmd::get_console_os()
{
    return m_console_os;
}

std::shared_ptr<esys::log::Mngr> Cmd::get_logger_mngr()
{
    if (m_logger_mngr == nullptr) m_logger_mngr = esys::log::Mngr::get();
    return m_logger_mngr;
}

const std::string &Cmd::get_logger_name() const
{
    return m_logger_name;
}

void Cmd::set_logger_name(const std::string &logger_name)
{
    m_logger_name = logger_name;
}

int Cmd::create_logger(const std::string &path)
{
    auto logger = get_logger_mngr()->new_logger(log::LoggerType::SPDLOG, get_logger_name());
    if (logger == nullptr) return -1;

    log::Level level = log::Level::DEBUG;

    logger->add_console(level);
    boost::filesystem::path log_path = path;
    if (log_path.empty()) log_path = boost::filesystem::current_path();
    log_path /= "log.txt";
    logger->add_basic_file(log_path.string());
    logger->set_log_level(level);
    logger->set_debug_level(5);
    logger->set_flush_log_level(level);
    set_logger_if(logger);
    return 0;
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

void Cmd::set_print_cmd_name_by_base(bool print_cmd_name_by_base)
{
    m_print_cmd_name_by_base = print_cmd_name_by_base;
}

bool Cmd::get_print_cmd_name_by_base() const
{
    return m_print_cmd_name_by_base;
}

std::shared_ptr<GitHelper> Cmd::new_git_helper()
{
    auto git_helper = std::make_shared<GitHelper>(get_git(), get_logger_if());

    get_git()->set_logger_if(git_helper);
    return git_helper;
}

void Cmd::print_cmd_name()
{
    std::ostringstream oss;

    print_cmd_name(oss);
    info(oss.str());
}

void Cmd::print_cmd_name(std::ostream &os)
{
    os << get_name() + " ...";
}

Result Cmd::generic_error(int error)
{
    if (error < 0)
        return ESYSREPO_RESULT(ResultCode::CMD_GENERIC_RAW_ERROR, error);
    else
        return ESYSREPO_RESULT(ResultCode::OK);
}

} // namespace esys::repo::exe
