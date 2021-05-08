/*!
 * \file esys/repo/exe/test/cmdsync03.cpp
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

/*! \class CmdSync03 esys/repo/exe/test/cmdsync03.cpp "esys/repo/exe/test/cmdsync03.cpp"
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(CmdSync03)
{
    FixCmdSync m_fix_cmd_sync;

    m_fix_cmd_sync.set_temp_sub_folder("cmdsync03");
    m_fix_cmd_sync.set_manifest_url("ssh://git@gitlab.com/libesys/esysrepo/test_google_manifest.git");
   
    m_fix_cmd_sync.run();

    m_fix_cmd_sync.test_basic_files();

    int result;

    result = m_fix_cmd_sync.test_file_content("src/commit_b/test.txt", "b");
    ESYSTEST_REQUIRE_EQUAL(result, 0);
}

} // namespace test

} // namespace exe

} // namespace repo

} // namespace esys
