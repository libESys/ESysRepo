/*!
 * \file esys/repo/exe/test/cmdinit02.cpp
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

#include "esys/repo/test/esysrepo_t_prec.h"

#include <esys/repo/libgit2/git.h>
#include <esys/repo/exe/cmdinit.h>
#include <esys/repo/filesystem.h>

#include <boost/filesystem.hpp>

#include <iostream>

namespace esys::repo::exe::test
{

/*! \class CmdInit02 esys/repo/exe/test/cmdinit02.cpp
 * "esys/repo/exe/test/cmdinit02.cpp"
 *
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(CmdInit02)
{
    boost::filesystem::path file_path;

    auto &ctrl = repo::test::TestCaseCtrl::get();
    file_path = ctrl.delete_create_temp_folder("cmdinit02");
    ESYSTEST_REQUIRE_EQUAL(file_path.string().empty(), false);

    auto logger = ctrl.get_logger("logger", file_path.string());
    ESYSTEST_REQUIRE_NE(logger, nullptr);

    CmdInit cmd_init;

    file_path /= "manifest";
    cmd_init.set_url("https://gitlab.com/libesys/esysmodbus/manifest.git");
    cmd_init.set_workspace_path(file_path.string());
    cmd_init.set_logger_if(logger);

    Result result = cmd_init.run();
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);

    result = cmd_init.run();
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);
}

} // namespace esys::repo::exe::test
