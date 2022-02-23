/*!
 * \file esys/repo/cli/cmdenv_cli.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2022 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/cli/cmdenv.h"

#include <msword2md/cpp/string.h>

#include <termcolor/termcolor.hpp>

#include <vector>

namespace esys::repo::cli
{

//#include "esys/repo/cli/cmdenv_doc.cpp"

CmdEnv::CmdEnv(AppBase *app)
    : BaseType(app, "env")
{
}

CmdEnv::~CmdEnv() = default;

std::shared_ptr<po::options_description> CmdEnv::get_desc()
{
    return nullptr;
}

int CmdEnv::configure_cmd(CmdType &cmd)
{
    return 0;
}

int CmdEnv::print_help(std::ostream &os)
{
    // os << cmdversion_doc_strings;
    return 0;
}

} // namespace esys::repo::cli
