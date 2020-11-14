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

#include <esys/repo/exe/cmdinit.h>

#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/filesystem.hpp>

#include <iostream>
#include <iomanip>

ESysRepoExe::ESysRepoExe()
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

    m_desc = std::make_unique<po::options_description>("Allowed options");
    // clang-format off
    m_desc->add_options()
        ("help,h", "produce help message")
        ("command", po::value< std::string>(), "command to execute")
        ("subargs", po::value<std::vector<std::string> >(), "Arguments for command")
        ("verbose", po::value<int>()->default_value(0)->implicit_value(1), "set verbose level")
        ("debug", po::value<bool>()->default_value(false)->implicit_value(true), "set debug mode, default random variable")
        ;
    // clang-format on

    int result = parse(m_args, *m_desc.get(), p, m_vm, false);
    auto cmd_fct = find_cmd_fct(m_args[0]);

    if ((result < 0) || (cmd_fct == nullptr)) return -1;
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
        auto cmd_fct = find_cmd_fct(m_vm["command"].as<std::string>());
        if (cmd_fct == nullptr)
        {
            return -1;
        }
        return (this->*cmd_fct)();
    }

    return -1;
}

int ESysRepoExe::cmd_help()
{
    return -1;
}

int ESysRepoExe::cmd_init()
{
    po::positional_options_description p;
    p.add("command", 1).add("subargs", -1);

    po::options_description desc("Allowed options");

    // clang-format off
    desc.add_options()
        ("help,h", "produce help message")
        ("manifest-url,u", po::value<std::string>()->required(), "manifest repository location")
        ("manifest-branch,b", po::value<std::string>(), "manifest branch or revision")
        ("manifest-name,m", po::value<std::string>(), "initial manifest file")
        ("google,g", po::value<bool>()->default_value(false)->implicit_value(true), "google manifest")
        ("git-super,s", po::value<bool>()->default_value(false)->implicit_value(true), "git super project")
        ;
    // clang-format on

    int result = parse(m_args, desc, p, m_vm);
    if (result < 0) return 0;

    esys::repo::exe::CmdInit init;

    init.set_url(m_vm["manifest-url"].as<std::string>());
    if (m_vm.count("manifest-branch")) init.set_branch(m_vm["manifest-branch"].as<std::string>());
    if (m_vm.count("manifest-name")) init.set_manifest_name(m_vm["manifest-name"].as<std::string>());
    init.set_google_manifest(m_vm["google"].as<bool>());

    return init.run();
}

int ESysRepoExe::cmd_info()
{
    return -1;
}

int ESysRepoExe::cmd_list()
{
    return -1;
}

int ESysRepoExe::cmd_status()
{
    return -1;
}

int ESysRepoExe::cmd_sync()
{
    return -1;
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
