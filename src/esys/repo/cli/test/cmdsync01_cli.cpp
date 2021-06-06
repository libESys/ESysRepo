/*!
 * \file esys/repo/cli/test/cmdsync01.cpp
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

#include <esys/repo/cli/cmdsync.h>

namespace esys
{

namespace repo
{

namespace cli
{

namespace test
{

/*! \class CmdSync01Cli esys/repo/cli/test/cmdsync01_cli.cpp
 * "esys/repo/cli/test/cmdsync01_cli.cpp"
 *
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(CmdSync01Cli)
{
    CmdSync cmd_sync;
    int job_count = 4;
    std::vector<std::string> args;
    int result = 0;

    args = {"sync"};
    cmd_sync.set_args(args);
    result = cmd_sync.parse_and_configure();
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    args = {"sync", "-j", std::to_string(job_count)};
    cmd_sync.set_args(args);
    result = cmd_sync.parse_and_configure();
    ESYSTEST_REQUIRE_EQUAL(result, 0);
    ESYSTEST_REQUIRE_EQUAL(cmd_sync.get_cmd().get_job_count(), job_count);
}

} // namespace test

} // namespace cli

} // namespace repo

} // namespace esys
