/*!
 * \file esys/repo/cli/cmdhelp_cli.cpp
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
#include "esys/repo/cli/cmdhelp.h"

namespace esys
{

namespace repo
{

namespace cli
{

CmdHelp::CmdHelp(AppBase *app)
    : BaseType(app, "help")
{
}

CmdHelp::~CmdHelp()
{
}

std::shared_ptr<po::options_description> CmdHelp::get_desc()
{
    return nullptr;
}

int CmdHelp::configure_cmd(CmdType &cmd)
{
    return 0;
}

} // namespace cli

} // namespace repo

} // namespace esys