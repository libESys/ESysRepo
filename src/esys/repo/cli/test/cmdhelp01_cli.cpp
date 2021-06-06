/*!
 * \file esys/repo/cli/test/cmdhelp01.cpp
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

#include "esys/repo/test/esysrepo_t_prec.h"

#include <esys/repo/cli/cmdhelp.h>

namespace esys
{

namespace repo
{

namespace cli
{

namespace test
{

/*! \class CmdHelp01Cli esys/repo/cli/test/cmdhelp01_cli.cpp "esys/repo/cli/test/cmdhelp01_cli.cpp"
 *
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(CmdHelp01Cli)
{
    CmdHelp cmd_help;
    std::vector<std::string> args;
    int result = 0;

    args = {};
    cmd_help.set_args(args);
    result = cmd_help.parse_and_configure();
    ESYSTEST_REQUIRE_NE(result, 0);

    args = {"help"};
    cmd_help.set_args(args);
    result = cmd_help.parse_and_configure();
    ESYSTEST_REQUIRE_EQUAL(result, 0);
}

} // namespace test

} // namespace cli

} // namespace repo

} // namespace esys
