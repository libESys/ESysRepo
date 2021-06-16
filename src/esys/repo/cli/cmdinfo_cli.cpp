/*!
 * \file esys/repo/cli/cmdinfo_cli.cpp
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
#include "esys/repo/cli/cmdinfo.h"

#include <msword2md/cpp/string.h>

#include <termcolor/termcolor.hpp>

#include <boost/filesystem.hpp>

#include <vector>

namespace esys
{

namespace repo
{

namespace cli
{

#include "esys/repo/cli/cmdinfo_doc.cpp"

CmdInfo::CmdInfo(AppBase *app)
    : BaseType(app, "info")
{
}

CmdInfo::~CmdInfo()
{
}

std::shared_ptr<po::options_description> CmdInfo::get_desc()
{
    auto desc = Cmd::get_desc();
    if (desc != nullptr) return desc;

    desc = std::make_shared<po::options_description>("Info options");
    // clang-format off
    desc->add_options()
        ("help,h", "produce help message")
        ("diff,d", po::value<bool>()->default_value(false)->implicit_value(true),
                        "show full info and commit diff including remote"
                        "branches")
        ("overview,o", po::value<bool>()->default_value(false)->implicit_value(true), "Show overview of all local commits")
        ("current-branch,b", po::value<bool>()->default_value(false)->implicit_value(true), "Consider only checked out branches")
        ("local-only,l", po::value<bool>()->default_value(false)->implicit_value(true), "Disable all remote operations")
        ;
    // clang-format on
    Cmd::set_desc(desc);
    return desc;
}

int CmdInfo::configure_cmd(CmdType &cmd)
{
    if (m_vm["diff"].as<bool>()) cmd.set_diff(true);
    if (m_vm["overview"].as<bool>()) cmd.set_overview(true);
    if (m_vm["current-branch"].as<bool>()) cmd.set_current_branch(true);
    if (m_vm["local-only"].as<bool>()) cmd.set_local_only(true);

    return 0;
}

int CmdInfo::print_help(std::ostream &os)
{
    os << cmdinfo_doc_strings;
    return 0;
}

} // namespace cli

} // namespace repo

} // namespace esys