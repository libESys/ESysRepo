/*!
 * \file esys/repo/cli/test/cmdinit01.cpp
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

#include <esys/repo/cli/cmdinit.h>

namespace esys
{

namespace repo
{

namespace cli
{

namespace test
{

/*! \class CmdInit01Cli esys/repo/cli/test/cmdinit01_cli.cpp
 * "esys/repo/cli/test/cmdinit01_cli.cpp"
 *
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(CmdInit01Cli)
{
    CmdInit cmd_init;
    std::string url = "https://gitlab.com/libesys/esysmodbus/manifest.git";
    std::vector<std::string> args;
    int result = 0;

    args = {};
    cmd_init.set_args(args);
    result = cmd_init.parse_and_configure();
    ESYSTEST_REQUIRE_NE(result, 0);

    args = {"-u", url};
    cmd_init.set_args(args);
    result = cmd_init.parse_and_configure();
    ESYSTEST_REQUIRE_EQUAL(result, 0);
    ESYSTEST_REQUIRE_EQUAL(cmd_init.get_cmd().get_url(), url);
}

} // namespace test

} // namespace cli

} // namespace repo

} // namespace esys
