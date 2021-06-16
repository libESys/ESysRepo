/*!
 * \file esys/repo/cli/cmdversion_cli.cpp
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
#include "esys/repo/cli/cmdversion.h"

#include <msword2md/cpp/string.h>

#include <termcolor/termcolor.hpp>

#include <vector>

namespace esys
{

namespace repo
{

namespace cli
{

#include "esys/repo/cli/cmdversion_doc.cpp"

CmdVersion::CmdVersion(AppBase *app)
    : BaseType(app, "version")
{
}

CmdVersion::~CmdVersion()
{
}

std::shared_ptr<po::options_description> CmdVersion::get_desc()
{
    return nullptr;
}

int CmdVersion::configure_cmd(CmdType &cmd)
{
    return 0;
}

int CmdVersion::print_help(std::ostream &os)
{
    os << cmdversion_doc_strings;
    return 0;
}

} // namespace cli

} // namespace repo

} // namespace esys