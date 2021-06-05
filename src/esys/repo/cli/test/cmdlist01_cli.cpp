/*!
 * \file esys/repo/cli/test/cmdlist01.cpp
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

#include <esys/repo/cli/cmdlist.h>

namespace esys
{

namespace repo
{

namespace cli
{

namespace test
{

/*! \class CmdList01Cli esys/repo/cli/test/cmdlist01_cli.cpp
 * "esys/repo/cli/test/cmdlist01_cli.cpp"
 *
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(CmdList01Cli)
{
    CmdList cmd_list;
    std::vector<std::string> args;
    int result = 0;

    args = {"list"};
    cmd_list.set_args(args);
    result = cmd_list.parse_and_configure();
    ESYSTEST_REQUIRE_EQUAL(result, 0);
}

} // namespace test

} // namespace cli

} // namespace repo

} // namespace esys
