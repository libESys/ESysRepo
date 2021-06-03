/*!
 * \file esys/repo/cli/cmd_cli.cpp
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
#include "esys/repo/cli/cmd.h"
#include "esys/repo/cli/appbase.h"

#include <boost/program_options/parsers.hpp>

#include <cassert>

namespace esys
{

namespace repo
{

namespace cli
{

Cmd::Cmd(AppBase *app, const std::string &name)
    : esys::log::User()
    , m_name(name)
    , m_app(app)
{
    m_positional.add("command", 1).add("subargs", -1);

    if (app != nullptr) app->register_cmd(this);
}

Cmd::~Cmd()
{
}

void Cmd::set_name(const std::string &name)
{
    m_name = name;
}

const std::string &Cmd::get_name() const
{
    return m_name;
}

void Cmd::set_app(AppBase *app)
{
    m_app = app;
}

AppBase *Cmd::get_app()
{
    return m_app;
}

std::shared_ptr<po::options_description> Cmd::get_common_desc()
{
    if (m_common_desc != nullptr) return m_common_desc;

    m_common_desc = std::make_shared<po::options_description>("Options");
    // clang-format off
    m_common_desc->add_options()
        ("help,h", "Produce help message")
        ("command", po::value<std::string>(), "Command to execute")
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
    return m_common_desc;
}

std::shared_ptr<po::options_description> Cmd::get_desc()
{
    return m_desc;
}

void Cmd::set_desc_all(std::shared_ptr<po::options_description> desc_all)
{
    m_desc_all = desc_all;
}

std::shared_ptr<po::options_description> Cmd::get_desc_all()
{
    if (m_desc_all != nullptr) return m_desc_all;

    m_desc_all = std::make_shared<po::options_description>("Allowed options");
    m_desc_all->add(*get_common_desc()).add(*get_desc());

    return m_desc_all;
}

void Cmd::set_args(const std::vector<std::string> &args)
{
    m_args = args;
}

std::vector<std::string> &Cmd::get_args()
{
    return m_args;
}

const std::vector<std::string> &Cmd::get_args() const
{
    return m_args;
}

int Cmd::parse(bool strict)
{
    bool parse_error = false;

    m_to_parse_further.clear();
    m_vm.clear();

    try
    {
        if (strict == false)
        {
            po::parsed_options parsed = po::command_line_parser(get_args())
                                            .options(*get_desc_all())
                                            .positional(m_positional)
                                            .allow_unregistered()
                                            .run();
            m_to_parse_further = po::collect_unrecognized(parsed.options, po::include_positional);
            po::store(parsed, m_vm);
        }
        else
        {
            po::parsed_options parsed =
                po::command_line_parser(get_args()).options(*get_desc_all()).positional(m_positional).run();
            m_to_parse_further = po::collect_unrecognized(parsed.options, po::include_positional);
            po::store(parsed, m_vm);
        }
        po::notify(m_vm);
    }
    catch (po::error &e)
    {
        parse_error = true;
        error(e.what());
    }

    if (parse_error) return -1;
    return 0;
}

int Cmd::configure_cmd(exe::Cmd &cmd)
{
    cmd.set_workspace_path(get_workspace());
    cmd.set_folder(get_folder());
    cmd.set_debug(get_debug());
    cmd.set_sub_args(get_sub_args());
    cmd.set_time(get_time());
    cmd.set_delta_time(get_delta_time());
    // \TODO add all missing data
    return 0;
}

bool Cmd::is_help()
{
    return is_present("help");
}

std::string Cmd::get_command()
{
    return get_string("command");
}

bool Cmd::get_time()
{
    return get_bool("time");
}

bool Cmd::get_delta_time()
{
    return get_bool("delta-time");
}

bool Cmd::get_public()
{
    return get_bool("public");
}

int Cmd::get_verbose()
{
    return get_int("verbose", 0);
}

bool Cmd::get_debug()
{
    return get_bool("debug");
}

std::string Cmd::get_workspace()
{
    return get_string("workspace");
}

std::string Cmd::get_folder()
{
    return get_string("folder");
}

std::vector<std::string> Cmd::get_sub_args()
{
    if (m_vm.count("subargs") == 0) return std::vector<std::string>();

    return m_vm["subargs"].as<std::vector<std::string>>();
}

void Cmd::set_desc(std::shared_ptr<po::options_description> desc)
{
    m_desc = desc;
}

std::string Cmd::get_string(const std::string &name)
{
    if (m_vm.count(name)) return m_vm[name].as<std::string>();
    return "";
}

bool Cmd::is_present(const std::string &name)
{
    return m_vm.count(name) > 0;
}

bool Cmd::get_bool(const std::string &name)
{
    if (m_vm.count(name)) return m_vm[name].as<bool>();
    return false;
}

int Cmd::get_int(const std::string &name, int dflt)
{
    if (m_vm.count(name)) return m_vm[name].as<int>();
    return dflt;
}

} // namespace cli

} // namespace repo

} // namespace esys