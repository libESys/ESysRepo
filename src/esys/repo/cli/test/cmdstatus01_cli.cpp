/*!
 * \file esys/repo/cli/test/cmdsatus01.cpp
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

#include <esys/repo/cli/cmdstatus.h>

namespace esys
{

namespace repo
{

namespace cli
{

namespace test
{

/*! \class CmdStatus01Cli esys/repo/cli/test/cmdstatus01_cli.cpp
 * "esys/repo/cli/test/cmdstatus01_cli.cpp"
 *
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(CmdStatus01Cli)
{
    CmdStatus cmd_status;
    std::vector<std::string> args;
    int result = 0;

    args = {"status"};
    cmd_status.set_args(args);
    result = cmd_status.parse_and_configure();
    ESYSTEST_REQUIRE_EQUAL(result, 0);
}

} // namespace test

} // namespace cli

} // namespace repo

} // namespace esys
