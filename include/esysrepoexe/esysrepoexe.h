/*!
 * \file esysepoexe/esysepoexe.h
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

#pragma once

#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>

#include <string>
#include <ostream>
#include <vector>
#include <memory>
#include <map>

namespace po = boost::program_options;

class ESysRepoExe
{
public:
    typedef int (ESysRepoExe::*CmdFctType)();

    ESysRepoExe();
    ~ESysRepoExe();

    void set_args(int argc, char **argv);
    int parse_args();
    int run();

    bool get_debug();

    int cmd_help();
    int cmd_init();
    int cmd_info();
    int cmd_list();
    int cmd_status();
    int cmd_sync();

    void set_os(std::ostream &os);
    std::ostream *get_os();

    void print_help(std::ostream &os);

    void set_error_msg(const std::string &error_msg);
    const std::string &get_error_msg();

    std::string get_input_filename();
    std::string get_output_filename();
    std::string get_base_dir();

    int parse(const std::vector<std::string> &args, po::options_description &desc, po::positional_options_description &p,
              po::variables_map &vm, bool strict = true);

    CmdFctType find_cmd_fct(const std::string &cmd);

protected:
    std::ostream *m_os = nullptr;
    int m_argc = 0;
    char **m_argv = nullptr;
    std::vector<std::string> m_args;
    po::variables_map m_vm;
    std::unique_ptr<po::options_description> m_desc;
    std::vector<std::string> m_to_parse_further;
    bool m_parse_error = false;
    std::string m_error_msg;
    std::map<std::string, CmdFctType> m_map_commands = {
        {"help", &ESysRepoExe::cmd_help}, {"init", &ESysRepoExe::cmd_init},     {"info", &ESysRepoExe::cmd_info},
        {"list", &ESysRepoExe::cmd_list}, {"status", &ESysRepoExe::cmd_status}, {"sync", &ESysRepoExe::cmd_sync},
    };
};
