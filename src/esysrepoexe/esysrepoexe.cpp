/*!
 * \file esysrepoexe/esysrepoexe.cpp
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

#include "esysrepoexe/esysrepoexe_prec.h"
#include "esysrepoexe/esysrepoexe.h"
#include "esysrepoexe/version.h"

#include <esys/repo/libgit2/git.h>
#include <esys/repo/exe/cmdinit.h>
#include <esys/repo/exe/cmdsync.h>
#include <esys/repo/exe/cmdlist.h>
#include <esys/repo/exe/cmdinfo.h>
#include <esys/repo/exe/cmdstatus.h>

#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/filesystem.hpp>

#include <iostream>
#include <iomanip>

ESysRepoExe::ESysRepoExe()
    : esys::log::User()
{
}

ESysRepoExe::~ESysRepoExe()
{
}

void ESysRepoExe::set_os(std::ostream &os)
{
    m_os = &os;
}

std::ostream *ESysRepoExe::get_os()
{
    return m_os;
}

void ESysRepoExe::set_args(int argc, char **argv)
{
    int i;

    m_args.clear();

    m_argc = argc;

    m_executable = argv[0];
    m_executable = boost::filesystem::absolute(m_executable).normalize().make_preferred();

    for (i = 1; i < argc; ++i)
    {
#ifdef WIN32
        std::vector<std::string> temp_args = po::split_winmain(argv[i]);
        m_args.insert(m_args.end(), temp_args.begin(), temp_args.end());
#else
        std::string temp = argv[i];
        m_args.push_back(temp);
#endif
    }
}

int ESysRepoExe::parse_args()
{
    po::positional_options_description p;
    p.add("command", 1).add("subargs", -1);

    m_desc = std::make_unique<po::options_description>("Options");
    // clang-format off
    m_desc->add_options()
        ("help,h", "Produce help message")
        ("command", po::value< std::string>(), "Command to execute")
        ("subargs", po::value<std::vector<std::string>>(), "Arguments for command")
        ("time", po::value<bool>()->default_value(false)->implicit_value(true), "Display timestamp")
        ("delta-time", po::value<bool>()->default_value(false)->implicit_value(true), "Display delta timestamp")
        ("public", po::value<bool>()->default_value(false)->implicit_value(true), "Only use https when possible")
        ("log", po::value<std::vector<std::string>>(), "Log execution to a file")
        ("verbose", po::value<int>()->default_value(0)->implicit_value(1), "Set verbose level")
        ("debug", po::value<bool>()->default_value(false)->implicit_value(true), "Set debug mode")
        ;
    // clang-format on

    int result = parse(m_args, *m_desc.get(), p, m_vm, false);
    auto cmd_fct = find_cmd_fct(m_args[0]);

    if ((result < 0) || (cmd_fct == nullptr))
    {
        if (result < 0)
        {
            return -1;
        }
        if (cmd_fct == nullptr)
        {
            error("Comamnd '" + m_args[0] + "' is not known.");
            return -1;
        }

        return -1;
    }

    if (m_logger_mngr == nullptr) m_logger_mngr = esys::log::Mngr::get();
    
    boost::filesystem::path plugin_search_folder = m_executable.parent_path();
    plugin_search_folder /= "plugins";
    plugin_search_folder /= "esyslog";
    m_logger_mngr->set_search_folder(plugin_search_folder.make_preferred().string());
    m_logger = m_logger_mngr->new_logger(esys::log::LoggerType::SPDLOG, "esysrepo");
    if (m_logger != nullptr)
    {
        set_logger_if(m_logger);

        if (m_vm["debug"].as<bool>())
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

bool ESysRepoExe::get_debug()
{
    return m_vm["debug"].as<bool>();
}

int ESysRepoExe::run()
{
    if (m_vm.count("command"))
    {
        std::string cmd = m_vm["command"].as<std::string>();
        auto cmd_fct = find_cmd_fct(cmd);
        if (cmd_fct == nullptr)
        {
            error("Comamnd '" + cmd + "' is not known.");
            return -1;
        }
        m_git = std::make_shared<esys::repo::libgit2::Git>();
        m_vm.clear();
        return (this->*cmd_fct)();
    }

    error("A comamnd must be provided.");
    return -1;
}

int ESysRepoExe::cmd_help()
{
    error("Comamnd 'help' not implemented yet.");
    return -1;
}

int ESysRepoExe::cmd_init()
{
    po::positional_options_description p;
    p.add("command", 1).add("subargs", -1);

    po::options_description desc("Init options");
    po::options_description desc_all("Allowed options");
    po::options_description desc_help("Options");

    // clang-format off
    desc.add_options()
        ("help,h", "produce help message")
        ("manifest-url,u", po::value<std::string>()->required(), "manifest repository location")
        ("manifest-branch,b", po::value<std::string>(), "manifest branch or revision")
        ("manifest-name,m", po::value<std::string>(), "initial manifest file")
        ("google,g", po::value<bool>()->default_value(false)->implicit_value(true), "google manifest")
        ("git-super,s", po::value<bool>()->default_value(false)->implicit_value(true), "git super project")
        ("output,o", po::value<std::string>(), "the output folder")
        ;
    // clang-format on
    desc_all.add(desc).add(*m_desc);

    int result = parse(m_args, desc_all, p, m_vm);
    if (result < 0) return 0;

    esys::repo::exe::CmdInit init;

    init.set_git(m_git);
    if (m_logger != nullptr) init.set_logger_if(m_logger);

    init.set_url(m_vm["manifest-url"].as<std::string>());
    if (m_vm.count("manifest-branch")) init.set_branch(m_vm["manifest-branch"].as<std::string>());
    if (m_vm.count("manifest-name")) init.set_manifest_name(m_vm["manifest-name"].as<std::string>());
    if (m_vm.count("google")) init.set_google_manifest(m_vm["google"].as<bool>());
    if (m_vm.count("git-super")) init.set_google_manifest(m_vm["git-super"].as<bool>());

    if (m_vm.count("output"))
    {
        boost::filesystem::path path = m_vm["output"].as<std::string>();
        path = boost::filesystem::absolute(path).normalize().make_preferred();
        init.set_parent_path(path.string());
    }
    init.set_google_manifest(m_vm["google"].as<bool>());

    return init.run();
}

int ESysRepoExe::cmd_info()
{
    po::positional_options_description p;
    p.add("command", 1).add("subargs", -1);

    po::options_description desc("Info options");
    po::options_description desc_all("Allowed options");
    po::options_description desc_help("Options");

    // clang-format off
    desc.add_options()
        ("help,h", "produce help message")
        ("diff,d", po::value<bool>()->default_value(false)->implicit_value(true),
                        "show full info and commit diff including remote"
                        "branches")
        ("overview,o", po::value<bool>()->default_value(false)->implicit_value(true), "Show overview of all local commits")
        ("current-branch,b", po::value<bool>()->default_value(false)->implicit_value(true), "Consider only checked out branches")
        ("local-only,l", po::value<bool>()->default_value(false)->implicit_value(true), "Disable all remote operations")
        ("folder", po::value<std::string>(), "The esysrepo folder to use")
        ;
    // clang-format on
    desc_all.add(desc).add(*m_desc);

    int result = parse(m_args, desc_all, p, m_vm);
    if (result < 0) return 0;

    esys::repo::exe::CmdInfo info;

    info.set_git(m_git);
    if (m_logger != nullptr) info.set_logger_if(m_logger);

    if (m_vm["debug"].as<bool>()) info.set_debug(true);
    if (m_vm["diff"].as<bool>()) info.set_diff(true);
    if (m_vm["overview"].as<bool>()) info.set_overview(true);
    if (m_vm["current-branch"].as<bool>()) info.set_current_branch(true);
    if (m_vm["local-only"].as<bool>()) info.set_local_only(true);

    result = info.set_folder(get_folder());
    if (result < 0) return result;

    return info.run();
}

int ESysRepoExe::cmd_list()
{
    po::positional_options_description p;
    p.add("command", 1).add("subargs", -1);

    po::options_description desc("List options");
    po::options_description desc_all("Allowed options");
    po::options_description desc_help("Options");

    // clang-format off
    desc.add_options()
        ("help,h", "produce help message")
        ("fullpath,f", po::value<bool>()->default_value(false)->implicit_value(true),
                        "Display the full work tree path instead of the"
                        "relative path")
        ("name-only,n", po::value<bool>()->default_value(false)->implicit_value(true), "Display only the name of the repository")
        ("path-only,p", po::value<bool>()->default_value(false)->implicit_value(true), "Display only the path of the repository")
        ("folder", po::value<std::string>(), "the esysrepo folder to use")
        ;
    // clang-format on
    desc_all.add(desc).add(*m_desc);

    int result = parse(m_args, desc_all, p, m_vm);
    if (result < 0) return 0;

    esys::repo::exe::CmdList list;

    list.set_git(m_git);
    if (m_logger != nullptr) list.set_logger_if(m_logger);

    if (m_vm["debug"].as<bool>()) list.set_debug(true);
    if (m_vm["fullpath"].as<bool>()) list.set_fullpath(true);
    if (m_vm["name-only"].as<bool>()) list.set_name_only(true);
    if (m_vm["path-only"].as<bool>()) list.set_path_only(true);

    result = list.set_folder(get_folder());
    if (result < 0) return result;

    return list.run();
}

int ESysRepoExe::cmd_status()
{
    po::positional_options_description p;
    p.add("command", 1).add("subargs", -1);

    po::options_description desc("Status options");
    po::options_description desc_all("Allowed options");
    po::options_description desc_help("Options");

    // clang-format off
    desc.add_options()
        ("help,h", "produce help message")
        ("quiet,q", po::value<bool>()->default_value(false)->implicit_value(true), "Only print the name of modified projects")
        ("folder", po::value<std::string>(), "the esysrepo folder to use")
        ;
    // clang-format on
    desc_all.add(desc).add(*m_desc);

    int result = parse(m_args, desc_all, p, m_vm);
    if (result < 0) return 0;

    esys::repo::exe::CmdStatus status;

    status.set_git(m_git);
    if (m_logger != nullptr) status.set_logger_if(m_logger);

    if (m_vm["debug"].as<bool>()) status.set_debug(true);
    if (m_vm["quiet"].as<bool>()) status.set_quiet(true);

    auto subargs = get_sub_args();

    status.set_sub_args(subargs);
    status.set_folder(get_folder());

    return status.run();
}

int ESysRepoExe::cmd_sync()
{
    po::positional_options_description p;
    p.add("command", 1).add("subargs", -1);

    po::options_description desc("Sync options");
    po::options_description desc_all("Allowed options");
    po::options_description desc_help("Options");

    // clang-format off
    desc.add_options()
        ("help,h", "produce help message")
        ("force-sync", po::value<bool>()->default_value(false)->implicit_value(true),
                        "overwrite an existing git directory if it needs to"
                        "point to a different object directory. WARNING: this"
                        "may cause loss of data")
        ("job,j", po::value<int>()->default_value(1), "projects to fetch simultaneously (default 1)")
        ("folder", po::value<std::string>(), "the esysrepo folder to use")
        ;
    // clang-format on
    desc_all.add(desc).add(*m_desc);

    int result = parse(m_args, desc_all, p, m_vm);
    if (result < 0) return 0;

    esys::repo::exe::CmdSync sync;

    sync.set_git(m_git);
    if (m_logger != nullptr) sync.set_logger_if(m_logger);

    if (m_vm["debug"].as<bool>()) sync.set_debug(true);

    if (m_vm.count("folder"))
    {
        boost::filesystem::path path = m_vm["folder"].as<std::string>();
        path = boost::filesystem::absolute(path).normalize().make_preferred();
        sync.set_parent_path(path.string());
    }
    else
    {
        boost::filesystem::path path = esys::repo::exe::Cmd::find_parent_path();
        if (path.empty())
        {
            error("Couldn't find a folder with esysrepo from : " + boost::filesystem::current_path().string());
            return -1;
        }
        sync.set_parent_path(path.string());
    }

    if (m_vm.count("job")) sync.set_job_count(m_vm["job"].as<int>());

    return sync.run();
}

int ESysRepoExe::cmd_version()
{
    std::ostringstream oss;

    oss << "Version ..." << std::endl;
    oss << std::setw(15) << std::left << "ESysRepo";
    oss << ESYSREPOEXE_VERSION_NUM_DOT_STRING << std::endl;

    oss << std::setw(15) << std::left << esys::repo::libgit2::Git::s_get_lib_name();
    oss << esys::repo::libgit2::Git::s_get_version() << std::endl;

    oss << std::setw(15) << std::left << esys::repo::libgit2::Git::s_get_ssh_lib_name();
    oss << esys::repo::libgit2::Git::s_get_ssh_version();

    info(oss.str());
    info("Version done.");
    return 0;
}

void ESysRepoExe::set_error_msg(const std::string &error_msg)
{
    m_error_msg = error_msg;
}

const std::string &ESysRepoExe::get_error_msg()
{
    return m_error_msg;
}

void ESysRepoExe::print_help(std::ostream &os)
{
    std::ostringstream oss;

    if (m_desc == nullptr) return;
    oss << *m_desc;

    os << oss.str();
}

std::string ESysRepoExe::get_input_filename()
{
    std::string result = m_vm["input"].as<std::string>();

    return result;
}

std::string ESysRepoExe::get_output_filename()
{
    std::string result;

    if (m_vm.count("output") != 0) return m_vm["output"].as<std::string>();

    boost::filesystem::path filename = get_input_filename();
    boost::filesystem::path output = filename.parent_path() / (filename.stem().string() + ".md");
    return output.make_preferred().string();
}

std::string ESysRepoExe::get_base_dir()
{
    if (m_vm.count("base_dir") != 0) return m_vm["base_dir"].as<std::string>();

    return "";
}

int ESysRepoExe::parse(const std::vector<std::string> &args, po::options_description &desc,
                       po::positional_options_description &p, po::variables_map &vm, bool strict)
{
    bool parse_error = false;

    m_to_parse_further.clear();

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

ESysRepoExe::CmdFctType ESysRepoExe::find_cmd_fct(const std::string &cmd)
{
    auto it = m_map_commands.find(cmd);

    if (it == m_map_commands.end()) return nullptr;

    return it->second;
}

const std::string &ESysRepoExe::get_log_file_path()
{
    m_log_file_path = "log.txt";
    return m_log_file_path;
}

void ESysRepoExe::set_logger_mngr(std::shared_ptr<esys::log::Mngr> logger_mngr)
{
    m_logger_mngr = logger_mngr;
}

std::string ESysRepoExe::get_string(const std::string &name)
{
    if (m_vm.count(name)) return m_vm[name].as<std::string>();
    return "";
}

std::string ESysRepoExe::get_folder()
{
    return get_string("folder");
}

std::vector<std::string> ESysRepoExe::get_sub_args()
{
    if (m_vm.count("subargs") == 0) return std::vector<std::string>();

    return m_vm["subargs"].as<std::vector<std::string>>();
}
