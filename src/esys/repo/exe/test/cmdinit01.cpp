/*!
 * \file esys/repo/exe/test/cmdinit01.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2022 Michel Gillet
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

/*! \class CmdInit01 esys/repo/exe/test/cmdinit01.cpp
 * "esys/repo/exe/test/cmdinit01.cpp"
 *
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(CmdInit01)
{
    boost::filesystem::path file_path;

    auto &ctrl = repo::test::TestCaseCtrl::get();
    file_path = ctrl.delete_create_temp_folder("cmdinit01");
    ESYSTEST_REQUIRE_EQUAL(file_path.string().empty(), false);

    CmdInit cmd_init;
    cmd_init.create_logger(file_path.string());
    ESYSTEST_REQUIRE_NE(cmd_init.get_logger_if(), nullptr);

    file_path /= "manifest";
    cmd_init.set_url("https://gitlab.com/libesys/esysmodbus/manifest.git");
    cmd_init.set_workspace_path(file_path.string());

    Result result = cmd_init.run();
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);
}

} // namespace esys::repo::exe::test
