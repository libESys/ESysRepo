/*!
 * \file esys/repo/cli/appbase.h
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

#pragma once

#include "esys/repo/esysrepo_defs.h"
#include "esys/repo/gitbase.h"
#include "esys/repo/manifest/group.h"

#include "esys/repo/cli/cmdinit.h"

#include <esys/log/user.h>
#include <esys/log/mngr.h>

#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>

#include <boost/filesystem.hpp>

#include <string>
#include <ostream>
#include <vector>
#include <memory>
#include <map>

namespace po = boost::program_options;

namespace esys
{

namespace repo
{

namespace cli
{

class ESYSREPO_API Cmd;

class ESYSREPO_API AppBase : public esys::log::User
{
public:
    typedef int (AppBase::*CmdFctType)();

    AppBase();
    ~AppBase();

    void set_args(const std::vector<std::string> &args);
    const std::vector<std::string> &get_args() const;
    void set_args(int argc, char **argv);
    int parse_and_configure();
    int parse_args();
    int run();
    int setup_console_and_logs();

    std::string get_cmd();

    bool get_debug();

    int cmd_help();
    int cmd_init();
    int cmd_info();
    int cmd_list();
    int cmd_status();
    int cmd_sync();
    int cmd_manifest();
    int cmd_version();

    void register_cmd(Cmd *cmd);
    std::vector<Cmd *> &get_cmds();
    const std::vector<Cmd *> &get_cmds() const;
    Cmd *find_cmd(const std::string &name);

    void set_os(std::ostream &os);
    std::ostream *get_os();

    void print_help(std::ostream &os);

    void set_error_msg(const std::string &error_msg);
    const std::string &get_error_msg();

    std::string get_input_filename();
    std::string get_output_filename();
    std::string get_workspace_folder();
    std::string get_folder();

    int parse(const std::vector<std::string> &args, po::options_description &desc,
              po::positional_options_description &p, po::variables_map &vm, bool strict = true);

    CmdFctType find_cmd_fct(const std::string &cmd);

    const std::string &get_log_file_path();

    void set_logger_mngr(std::shared_ptr<esys::log::Mngr> logger_mngr);

    std::vector<std::string> get_sub_args();
    std::string get_string(const std::string &name);

    void set_version(const std::string &version);
    const std::string &get_version() const;

    std::shared_ptr<po::options_description> get_common_desc();

    static int groups_str_to_groups(const std::string &groups_str, std::vector<std::string> &groups);

protected:
    std::ostream *m_os = nullptr;
    int m_argc = 0;
    char **m_argv = nullptr;
    std::vector<std::string> m_args;
    boost::filesystem::path m_executable;
    po::variables_map m_vm;
    std::shared_ptr<po::options_description> m_common_desc;
    std::vector<std::string> m_to_parse_further;
    bool m_parse_error = false;
    std::string m_error_msg;
    std::shared_ptr<esys::repo::GitBase> m_git;
    std::string m_log_file_path;
    std::shared_ptr<esys::log::LoggerBase> m_logger;
    std::shared_ptr<esys::log::Mngr> m_logger_mngr;
    std::string m_version;
    std::map<std::string, CmdFctType> m_map_commands = {
        {"help", &AppBase::cmd_help},       {"init", &AppBase::cmd_init},        {"info", &AppBase::cmd_info},
        {"list", &AppBase::cmd_list},       {"status", &AppBase::cmd_status},    {"sync", &AppBase::cmd_sync},
        {"version", &AppBase::cmd_version}, {"manifest", &AppBase::cmd_manifest}};

    std::vector<Cmd *> m_cmds;
    std::map<std::string, Cmd *> m_map_cmds;
};

} // namespace cli

} // namespace repo

} // namespace esys
