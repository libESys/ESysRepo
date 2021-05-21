/*!
 * \file esys/repo/exe/test/cmdsync03.cpp
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
#include "esys/repo/exe/test/fixcmd.h"

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
    FixCmd m_fix_cmd_sync;

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
