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

#include <msword2md/cpp/string.h>

#include <termcolor/termcolor.hpp>

#include <vector>

namespace esys::repo::cli
{

#include "esys/repo/cli/cmdhelp_doc.cpp"

CmdHelp::CmdHelp(AppBase *app)
    : BaseType(app, "help")
{
}

CmdHelp::~CmdHelp() = default;

std::shared_ptr<po::options_description> CmdHelp::get_desc()
{
    return nullptr;
}

int CmdHelp::configure_cmd(CmdType &cmd)
{
    return 0;
}

int CmdHelp::print_help(std::ostream &os)
{
    os << cmdhelp_doc_strings;
    return 0;
}

} // namespace esys::repo::cli
