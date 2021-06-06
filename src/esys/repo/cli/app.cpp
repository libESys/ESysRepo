/*!
 * \file esys/repo/cli/app.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/cli/app.h"

namespace esys
{

namespace repo
{

namespace cli
{

App::App()
    : AppBase()
{
}

App::~App()
{
}

void App::set_version(const std::string &version)
{
    AppBase::set_version(version);
    get_cmd_version().get_cmd().set_version(version);
}

CmdHelp &App::get_cmd_help()
{
    return m_cmd_help;
}

CmdInfo &App::get_cmd_info()
{
    return m_cmd_info;
}

CmdInit &App::get_cmd_init()
{
    return m_cmd_init;
}

CmdList &App::get_cmd_list()
{
    return m_cmd_list;
}

CmdManifest &App::get_cmd_manifest()
{
    return m_cmd_manifest;
}

CmdStatus &App::get_cmd_status()
{
    return m_cmd_status;
}

CmdSync &App::get_cmd_sync()
{
    return m_cmd_sync;
}

CmdVersion &App::get_cmd_version()
{
    return m_cmd_version;
}

} // namespace cli

} // namespace repo

} // namespace esys
