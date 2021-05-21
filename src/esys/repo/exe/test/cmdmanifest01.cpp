/*!
 * \file esys/repo/exe/test/cmdmanifest01.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2021 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/test/esysrepo_t_prec.h"
#include "esys/repo/exe/test/fixcmd.h"

#include <esys/repo/manifest/repository.h>

#include <boost/filesystem.hpp>

namespace esys
{

namespace repo
{

namespace exe
{

namespace test
{

/*! \class CmdManifest01 esys/repo/exe/test/cmdmanifest01.cpp "esys/repo/exe/test/cmdmanifest01.cpp"
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(CmdManifest01)
{
    FixCmd fix_cmd;
    boost::filesystem::path output_path;

    /*auto &ctrl = repo::test::TestCaseCtrl::get();
    output_path = ctrl.delete_create_temp_folder("cmdmanifest01");
    ESYSTEST_REQUIRE_EQUAL(output_path.string().empty(), false);

    auto logger = ctrl.get_logger("logger", output_path.string());
    ESYSTEST_REQUIRE_NE(logger, nullptr); */

    fix_cmd.set_temp_sub_folder("cmdmanifest01");
    fix_cmd.set_manifest_url("ssh://git@gitlab.com/libesys/esysrepo/test_google_manifest.git");

    fix_cmd.init();

    fix_cmd.sync();

    output_path = fix_cmd.get_temp_folder();
    output_path /= "default.xml";

    fix_cmd.get_cmd_manifest().set_revision_as_head(true);
    fix_cmd.get_cmd_manifest().set_output_file(output_path.string());

    fix_cmd.manifest();

    auto manifest = fix_cmd.get_cmd_manifest().get_manifest();
    auto repo = manifest->find_repo_by_path("src/commit_a");
    ESYSTEST_REQUIRE_EQUAL(repo->get_revision(), "3a1c73ade6f3bd5112d9ae993d83612c1a4d85b2");

    repo = manifest->find_repo_by_path("src/commit_b");
    ESYSTEST_REQUIRE_EQUAL(repo->get_revision(), "0e4913adae332d19a23ca93cfdc62387b5f7e9ce");

    repo = manifest->find_repo_by_path("src/test_a");
    ESYSTEST_REQUIRE_EQUAL(repo->get_revision(), "3a1c73ade6f3bd5112d9ae993d83612c1a4d85b2");

    repo = manifest->find_repo_by_path("src/test_a_b");
    ESYSTEST_REQUIRE_EQUAL(repo->get_revision(), "9200c176d27a1ecb7d35edffc90b4a452e3902a8");

    repo = manifest->find_repo_by_path("src/test_b");
    ESYSTEST_REQUIRE_EQUAL(repo->get_revision(), "0e4913adae332d19a23ca93cfdc62387b5f7e9ce");

    repo = manifest->find_repo_by_path(".");
    ESYSTEST_REQUIRE_EQUAL(repo->get_revision(), "64280d3bed1531db5965fca8183cb68ad3770659");
}

} // namespace test

} // namespace exe

} // namespace repo

} // namespace esys
