/*!
 * \file esys/repo/exe/cmdhelp.cpp
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
#include "esys/repo/exe/cmdhelp.h"
#include "esys/repo/cli/appbase.h"

#include <termcolor/termcolor.hpp>

#include <sstream>
#include <iomanip>
#include <cassert>
#include <iostream>

namespace esys
{

namespace repo
{

namespace exe
{

CmdHelp::CmdHelp()
    : Cmd("Help")
{
}

CmdHelp::~CmdHelp()
{
}

int CmdHelp::impl_run()
{
    std::ostringstream oss;
    std::ostringstream oss_help;
    int result = 0;
    // info("Help ...");

    assert(get_app_base() != nullptr);

    cli::Cmd *cmd;

    if (get_sub_args().size() == 0)
    {
        error("At least one command should be given.");
        return -1;
    }

    for (auto &cmd_txt : get_sub_args())
    {
        oss.str("");
        cmd = get_app_base()->find_cmd(cmd_txt);
        if (cmd == nullptr)
        {
            error("Unknown command '" + cmd_txt + "'.");
            continue;
        }
        oss << "Command '" << cmd_txt << "':" << std::endl;
        result = cmd->print_help(oss_help);
        if (result < 0)
        {
            oss << *cmd->get_desc_all();
            info(oss.str());
        }
        else
        {
            info(oss.str());
            if (get_console_os() != nullptr)
                cmd->print_help(*get_console_os());
            else
                std::cout << oss_help.str();
        }
    }
    // info("Help done.");
    return 0;
}

} // namespace exe

} // namespace repo

} // namespace esys
