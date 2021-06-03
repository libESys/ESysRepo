/*!
 * \file esys/repo/cli/test/appbase01.cpp
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

#include <esys/repo/cli/appbase.h>
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
ESYSTEST_AUTO_TEST_CASE(AppBase01)
{
    std::string url = "https://gitlab.com/libesys/esysmodbus/manifest.git";
    std::vector<std::string> args;
    int result = 0;

    AppBase app_base;
    CmdInit cmd_init(&app_base);

    args = {};
    app_base.set_args(args);
    result = app_base.parse_and_configure();
    ESYSTEST_REQUIRE_NE(result, 0);

    args = {"init", "-u", url};
    app_base.set_args(args);
    result = app_base.parse_and_configure();
    ESYSTEST_REQUIRE_EQUAL(result, 0);
    ESYSTEST_REQUIRE_EQUAL(cmd_init.get_cmd().get_url(), url);
}

} // namespace test

} // namespace cli

} // namespace repo

} // namespace esys
