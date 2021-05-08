/*!
 * \file esys/repo/exe/test/cmdsync04.cpp
 * \brief
 *
 * \cond
 * __legal_b__
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
    git::Commit parent_commit;

    // Get the last commit in the manifest git repo
    result = m_fix_cmd_sync.get_git()->get_last_commit(last_commit);
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    // Get the its parent commit
    result = m_fix_cmd_sync.get_git()->get_parent_commit(last_commit, parent_commit);
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    // Reset the manifest git repo to the parent commit
    result = m_fix_cmd_sync.get_git()->reset(parent_commit, git::ResetType::HARD);
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    git::Commit new_last_commit;

    // Get the new last commit
    result = m_fix_cmd_sync.get_git()->get_last_commit(new_last_commit);
    ESYSTEST_REQUIRE_EQUAL(result, 0);
    result = m_fix_cmd_sync.close_git();
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    // The new last commit should be the parent commit
    ESYSTEST_REQUIRE_EQUAL(parent_commit.get_hash(), new_last_commit.get_hash());
   
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
}

} // namespace test

} // namespace exe

} // namespace repo

} // namespace esys