/*!
 * \file esys/repo/cli/appbase.cpp
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
#include "esys/repo/cli/appbase.h"
#include "esys/repo/version.h"
#include "esys/repo/cli/cmd.h"
#include "esys/repo/libgit2/git.h"

#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>

#ifndef WIN32
#include <boost/process/search_path.hpp>
#endif

#ifdef WIN32
#include <stdio.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

#endif

#include <iostream>
#include <iomanip>
#include <cassert>

namespace esys
{

namespace repo
{

namespace cli
{

AppBase::AppBase()
    : esys::log::User()
{
}

AppBase::~AppBase()
{
}

void AppBase::set_os(std::ostream &os)
{
    m_os = &os;
}

std::ostream *AppBase::get_os()
{
    return m_os;
}

void AppBase::register_cmd(Cmd *cmd)
{
    assert(find_cmd(cmd->get_name()) == nullptr);

    m_cmds.push_back(cmd);
    m_map_cmds[cmd->get_name()] = cmd;
}

std::vector<Cmd *> &AppBase::get_cmds()
{
    return m_cmds;
}

const std::vector<Cmd *> &AppBase::get_cmds() const
{
    return m_cmds;
}

Cmd *AppBase::find_cmd(const std::string &name)
{
    auto it = m_map_cmds.find(name);
    if (it == m_map_cmds.end()) return nullptr;
    return it->second;
}

void AppBase::set_args(const std::vector<std::string> &args)
{
    m_args = args;
}

const std::vector<std::string> &AppBase::get_args() const
{
    return m_args;
}

void AppBase::set_args(int argc, char **argv)
{
    int i;

    std::vector<std::string> args;

    m_argc = argc;

#ifdef WIN32
    m_executable = argv[0];
    m_executable = boost::filesystem::absolute(m_executable).normalize().make_preferred();
#else
    boost::filesystem::path temp_path = argv[0];
    m_executable = boost::process::search_path(temp_path.filename());
#endif

    for (i = 1; i < argc; ++i)
    {
#ifdef WIN32
        std::vector<std::string> temp_args = po::split_winmain(argv[i]);
        for (auto &temp_arg : temp_args) args.push_back(temp_arg);
#else
        std::string temp = argv[i];
        args.push_back(temp);
#endif
    }

    set_args(args);
}

int AppBase::parse_and_configure()
{
    int result = parse_args();
    if (result < 0) return result;

    if (get_cmd().empty())
    {
        //! TODO add logger message
        return -1;
    }
    auto cmd_obj = find_cmd(get_cmd());
    if (cmd_obj == nullptr)
    {
        //! TODO add logger message
        return -1;
    }

    cmd_obj->set_logger_if(get_logger_if());
    cmd_obj->set_args(get_args());
    return cmd_obj->parse_and_configure();
}

int AppBase::parse_args()
{
    setup_console_and_logs();

    po::positional_options_description p;
    p.add("command", 1).add("subargs", -1);

    if (m_common_desc == nullptr)
    {
        m_common_desc = std::make_shared<po::options_description>("Options");
        // clang-format off
        m_common_desc->add_options()
            ("help,h", "Produce help message")
            ("command", po::value< std::string>(), "Command to execute")
            ("subargs", po::value<std::vector<std::string>>(), "Arguments for command")
            ("time", po::value<bool>()->default_value(false)->implicit_value(true), "Display timestamp")
            ("delta-time", po::value<bool>()->default_value(false)->implicit_value(true), "Display delta timestamp")
            ("public", po::value<bool>()->default_value(false)->implicit_value(true), "Only use https when possible")
            ("log", po::value<std::vector<std::string>>(), "Log execution to a file")
            ("verbose", po::value<int>()->default_value(0)->implicit_value(1), "Set verbose level")
            ("debug", po::value<bool>()->default_value(false)->implicit_value(true), "Set debug mode")
            ("workspace,w", po::value<std::string>(), "the path to the workspade to use")
            ("folder,f", po::value<std::string>(), "the folder to work with")
            ;
        // clang-format on
    }

    return parse(m_args, *m_common_desc.get(), p, m_vm, false);
}

std::string AppBase::get_cmd()
{
    if (m_vm.count("command")) return m_vm["command"].as<std::string>();
    return "";
}

bool AppBase::get_debug()
{
    if (m_vm.count("debug")) return m_vm["debug"].as<bool>();
    return false;
}

int AppBase::setup_console_and_logs()
{
    bool debug = get_debug();

    if (m_logger_mngr == nullptr) m_logger_mngr = esys::log::Mngr::get();

    std::string plugin_search_folder;

    int result = esys::log::Mngr::get()->find_plugin_folder(plugin_search_folder);
    if (result < 0) std::cout << "ERROR: can't find ESysLog plugin folder." << std::endl;
    if (debug) std::cout << "plugin_search_folder = " << plugin_search_folder << std::endl;

    // m_logger_mngr->set_search_folder(plugin_search_folder.make_preferred().string());
    m_logger = m_logger_mngr->new_logger(esys::log::LoggerType::SPDLOG, "AppBase");
    if (m_logger != nullptr)
    {
        set_logger_if(m_logger);

        if (debug)
        {
            m_logger->add_console("[%^%l%$] %v", esys::log::Level::DEBUG);
            if (!get_log_file_path().empty()) m_logger->add_basic_file(get_log_file_path());
            m_logger->set_log_level(esys::log::Level::DEBUG);
            m_logger->set_debug_level(10);
            m_logger->set_flush_log_level(esys::log::Level::DEBUG);
        }
        else
        {
            m_logger->add_console("[%^%l%$] %v", esys::log::Level::INFO);
            if (!get_log_file_path().empty())
                m_logger->add_basic_file(get_log_file_path(), false, esys::log::Level::INFO);
            m_logger->set_log_level(esys::log::Level::INFO);
            m_logger->set_flush_log_level(esys::log::Level::INFO);
        }
    }
    return 0;
}

void AppBase::setup_terminal()
{
#ifdef WIN32
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        std::cout << "ERROR: couldn't get handle to standard output." << std::endl;
        return;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        std::cout << "ERROR: couldn't get windows console mode." << std::endl;
        return;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        std::cout << "ERROR: couldn't set virtual terminal processing mode." << std::endl;
        return;
    }
#endif
}

int AppBase::run()
{
    if (m_vm.count("command"))
    {
        std::string cmd = m_vm["command"].as<std::string>();

        auto cmd_obj = find_cmd(cmd);
        if (cmd_obj != nullptr)
        {
            m_git = std::make_shared<esys::repo::libgit2::Git>();
            m_vm.clear();
            cmd_obj->set_logger_if(get_logger_if());
            cmd_obj->set_console_os(get_os());
            return cmd_obj->run();
        }
        else
        {
            error("Comamnd '" + cmd + "' is not known.");
            return -1;
        }
    }

    error("A comamnd must be provided.");
    return -1;
}

void AppBase::set_error_msg(const std::string &error_msg)
{
    m_error_msg = error_msg;
}

const std::string &AppBase::get_error_msg()
{
    return m_error_msg;
}

void AppBase::print_help(std::ostream &os)
{
    std::ostringstream oss;

    if (m_common_desc == nullptr) return;
    oss << *m_common_desc;

    os << oss.str();
}

std::string AppBase::get_input_filename()
{
    std::string result = m_vm["input"].as<std::string>();

    return result;
}

std::string AppBase::get_output_filename()
{
    std::string result;

    if (m_vm.count("output") != 0) return m_vm["output"].as<std::string>();

    boost::filesystem::path filename = get_input_filename();
    boost::filesystem::path output = filename.parent_path() / (filename.stem().string() + ".md");
    return output.make_preferred().string();
}

int AppBase::parse(const std::vector<std::string> &args, po::options_description &desc,
                   po::positional_options_description &p, po::variables_map &vm, bool strict)
{
    bool parse_error = false;

    m_to_parse_further.clear();
    m_vm.clear();

    try
    {
        if (strict == false)
        {
            po::parsed_options parsed =
                po::command_line_parser(args).options(desc).positional(p).allow_unregistered().run();
            m_to_parse_further = po::collect_unrecognized(parsed.options, po::include_positional);
            po::store(parsed, vm);
        }
        else
        {
            po::parsed_options parsed = po::command_line_parser(args).options(desc).positional(p).run();
            m_to_parse_further = po::collect_unrecognized(parsed.options, po::include_positional);
            po::store(parsed, vm);
        }
        po::notify(m_vm);
    }
    catch (po::error &e)
    {
        parse_error = true;
        set_error_msg(e.what());
        std::cout << e.what() << std::endl << std::flush;
    }

    if (parse_error) return -1;
    return 0;
}

/*AppBase::CmdFctType AppBase::find_cmd_fct(const std::string &cmd)
{
    auto it = m_map_commands.find(cmd);

    if (it == m_map_commands.end()) return nullptr;

    return it->second;
} */

const std::string &AppBase::get_log_file_path()
{
    m_log_file_path = "log.txt";
    return m_log_file_path;
}

void AppBase::set_logger_mngr(std::shared_ptr<esys::log::Mngr> logger_mngr)
{
    m_logger_mngr = logger_mngr;
}

std::string AppBase::get_string(const std::string &name)
{
    if (m_vm.count(name)) return m_vm[name].as<std::string>();
    return "";
}

void AppBase::set_version(const std::string &version)
{
    m_version = version;
}

const std::string &AppBase::get_version() const
{
    return m_version;
}

std::shared_ptr<po::options_description> AppBase::get_common_desc()
{
    return m_common_desc;
}

int AppBase::groups_str_to_groups(const std::string &groups_str, std::vector<std::string> &groups)
{
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> sep(", ");
    tokenizer tokens(groups_str, sep);

    groups.clear();

    for (tokenizer::iterator it = tokens.begin(); it != tokens.end(); ++it) groups.push_back(*it);

    return 0;
}

std::string AppBase::get_workspace_folder()
{
    return get_string("workspace");
}

std::string AppBase::get_folder()
{
    return get_string("folder");
}

std::vector<std::string> AppBase::get_sub_args()
{
    if (m_vm.count("subargs") == 0) return std::vector<std::string>();

    return m_vm["subargs"].as<std::vector<std::string>>();
}

} // namespace cli

} // namespace repo

} // namespace esys
