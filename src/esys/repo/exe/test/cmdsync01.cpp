/*!
 * \file esys/repo/exe/test/cmdsync01.cpp
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

#include <esys/repo/libgit2/git.h>
#include <esys/repo/exe/cmdinit.h>
#include <esys/repo/exe/cmdsync.h>
#include <esys/repo/filesystem.h>

#include <boost/filesystem.hpp>

#include <iostream>

namespace esys
{

namespace repo
{

namespace exe
{

namespace test
{

/*! \class CmdSync01 esys/repo/exe/test/cmdsync01.cpp
 * "esys/repo/exe/test/cmdsync01.cpp"
 *
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(CmdSync01)
{
    boost::filesystem::path file_path;

    auto &ctrl = repo::test::TestCaseCtrl::get();
    file_path = ctrl.delete_create_temp_folder("cmdsync01");
    ESYSTEST_REQUIRE_EQUAL(file_path.string().empty(), false);

    auto logger = ctrl.get_logger("logger", file_path.string());
    ESYSTEST_REQUIRE_NE(logger, nullptr);

    CmdInit cmd_init;
    auto git = std::make_shared<libgit2::Git>();
    git->set_logger_if(logger);

    cmd_init.set_url("https://gitlab.com/libesys/esysmodbus/manifest.git");
    cmd_init.set_workspace_path(file_path.string());
    cmd_init.set_git(git);
    cmd_init.set_logger_if(logger);

    int result = cmd_init.run();
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    CmdSync cmd_sync;

    cmd_sync.set_job_count(4);
    cmd_sync.set_workspace_path(file_path.string());
    cmd_sync.set_git(git);
    cmd_sync.set_logger_if(logger);

    result = cmd_sync.run();
    ESYSTEST_REQUIRE_EQUAL(result, 0);
}

} // namespace test

} // namespace exe

} // namespace repo

} // namespace esys
