/*!
 * \file esys/repo/cli/cmd.h
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
#include "esys/repo/exe/cmd.h"

#include <esys/log/user.h>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>

#include <string>
#include <memory>
#include <vector>

namespace po = boost::program_options;

namespace esys
{

namespace repo
{

namespace cli
{

class ESYSREPO_API AppBase;

class ESYSREPO_API Cmd : public esys::log::User
{
public:
    Cmd(AppBase *app, const std::string &name);
    virtual ~Cmd();

    void set_name(const std::string &name);
    const std::string &get_name() const;

    void set_app(AppBase *app);
    AppBase *get_app();

    std::shared_ptr<po::options_description> get_common_desc();

    virtual std::shared_ptr<po::options_description> get_desc();

    void set_desc_all(std::shared_ptr<po::options_description> desc_all);
    virtual std::shared_ptr<po::options_description> get_desc_all();

    void set_args(const std::vector<std::string> &args);
    std::vector<std::string> &get_args();
    const std::vector<std::string> &get_args() const;

    int parse(bool strict = true);

    virtual int configure_cmd(exe::Cmd &cmd);

    virtual exe::Cmd &get_cmd_base() = 0;

    virtual int parse_and_configure() = 0;

    virtual int run() = 0;

    bool is_help();
    std::string get_command();
    bool get_time();
    bool get_delta_time();
    bool get_public();
    int get_verbose();
    bool get_debug();
    std::string get_workspace();
    std::string get_folder();
    std::vector<std::string> get_sub_args();

    static int groups_str_to_groups(const std::string &groups_str, std::vector<std::string> &groups);

protected:
    void set_desc(std::shared_ptr<po::options_description> desc);
    std::string get_string(const std::string &name);
    bool is_present(const std::string &name);
    bool get_bool(const std::string &name);
    int get_int(const std::string &name, int dflt = -1);

    std::string m_name;
    AppBase *m_app = nullptr;
    std::vector<std::string> m_args;
    po::positional_options_description m_positional;
    std::shared_ptr<po::options_description> m_common_desc;
    std::shared_ptr<po::options_description> m_desc;
    std::shared_ptr<po::options_description> m_desc_all;
    po::variables_map m_vm;
    std::vector<std::string> m_to_parse_further;
};

} // namespace cli

} // namespace repo

} // namespace esys