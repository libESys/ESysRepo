/*!
 * \file esys/repo/exe/test/cmdsync04.cpp
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
#include "esys/repo/exe/test/fixcmdsync.h"

namespace esys
{

namespace repo
{

namespace exe
{

namespace test
{

/*! \class CmdSync04 esys/repo/exe/test/cmdsync04.cpp "esys/repo/exe/test/cmdsync04.cpp"
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(CmdSync04)
{
    FixCmdSync m_fix_cmd_sync;

    m_fix_cmd_sync.set_temp_sub_folder("cmdsync04");
    m_fix_cmd_sync.set_manifest_url("ssh://git@gitlab.com/libesys/esysrepo/test_google_manifest.git");
    m_fix_cmd_sync.set_manifest_branch("commit_b");

    m_fix_cmd_sync.init();

    // Open the manifest git repo
    int result = m_fix_cmd_sync.open_git_manifest_repo();
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    git::Commit last_commit;

    // Get the last commit in the manifest git repo
    result = m_fix_cmd_sync.get_git()->get_last_commit(last_commit);
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    result = m_fix_cmd_sync.get_git()->reset_to_parent();
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    git::Commit new_last_commit;

    result = m_fix_cmd_sync.close_git();
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    // Sync the whole project, and the manifest should also be synced
    m_fix_cmd_sync.sync();

    // Open the manifest git repo
    result = m_fix_cmd_sync.open_git_manifest_repo();
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    // Get the last commit
    result = m_fix_cmd_sync.get_git()->get_last_commit(new_last_commit);
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    result = m_fix_cmd_sync.close_git();
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    // Verify that the manifest was also synced by verifying that the current last commit
    // is the same as the last commit before resetting the git repo.
    ESYSTEST_REQUIRE_EQUAL(last_commit.get_hash(), new_last_commit.get_hash());

    // Test that all git repos were synced correctly
    m_fix_cmd_sync.test_basic_files();

    result = m_fix_cmd_sync.test_file_content("src/commit_b/test.txt", "b");
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    auto manifest = m_fix_cmd_sync.get_cmd_sync().get_manifest();
    ESYSTEST_REQUIRE_NE(manifest, nullptr);

    auto repo = manifest->find_repo_by_path("src/test_a_b");

    boost::filesystem::path repo_path;
    repo_path = m_fix_cmd_sync.get_file_path();
    repo_path /= "src/test_a_b";

    ESYSTEST_REQUIRE_EQUAL(boost::filesystem::exists(repo_path), true);

    result = m_fix_cmd_sync.get_git()->open(repo_path.normalize().make_preferred().string());
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    result = m_fix_cmd_sync.get_git()->reset_to_parent();
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    result = m_fix_cmd_sync.close_git();
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    // Sync the whole project, and the manifest should also be synced
    m_fix_cmd_sync.sync();

    // Test that all git repos were synced correctly
    m_fix_cmd_sync.test_basic_files();
}

} // namespace test

} // namespace exe

} // namespace repo

} // namespace esys
