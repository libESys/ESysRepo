/*!
 * \file esys/repo/cli/cmdmanifest_cli.cpp
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
#include "esys/repo/cli/cmdstatus.h"

#include <boost/filesystem.hpp>

namespace esys
{

namespace repo
{

namespace cli
{

CmdStatus::CmdStatus(AppBase *app)
    : BaseType(app, "status")
{
}

CmdStatus::~CmdStatus()
{
}

std::shared_ptr<po::options_description> CmdStatus::get_desc()
{
    auto desc = Cmd::get_desc();
    if (desc != nullptr) return desc;

    desc = std::make_shared<po::options_description>("List options");
    // clang-format off
    desc->add_options()
        ("help,h", "produce help message")
        ("quiet,q", po::value<bool>()->default_value(false)->implicit_value(true), "Only print the name of modified projects")
        ;
    // clang-format on
    Cmd::set_desc(desc);
    return desc;
}

int CmdStatus::configure_cmd(CmdType &cmd)
{
    if (m_vm["quiet"].as<bool>()) cmd.set_quiet(true);

    return 0;
}

} // namespace cli

} // namespace repo

} // namespace esys