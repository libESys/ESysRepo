/*!
 * \file esys/repo/exe/test/cmdsync05.cpp
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

/*! \class CmdSync05 esys/repo/exe/test/cmdsync05.cpp "esys/repo/exe/test/cmdsync05.cpp"
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(CmdSync05)
{
    FixCmd m_fix_cmd_sync;

    m_fix_cmd_sync.set_temp_sub_folder("cmdsync05");
    m_fix_cmd_sync.set_manifest_url("ssh://git@gitlab.com/libesys/esysrepo/test_google_manifest.git");
    
    m_fix_cmd_sync.init();

    m_fix_cmd_sync.sync({"src/commit_a"});

    m_fix_cmd_sync.test_repo_exists("src/commit_a");
    m_fix_cmd_sync.test_repo_exists("src/commit_b", false);
    m_fix_cmd_sync.test_repo_exists("src/test_a", false);
    m_fix_cmd_sync.test_repo_exists("src/test_a_b", false);
    m_fix_cmd_sync.test_repo_exists("src/test_b", false);

    m_fix_cmd_sync.sync({"src/test_*"});

    m_fix_cmd_sync.test_repo_exists("src/commit_a");
    m_fix_cmd_sync.test_repo_exists("src/commit_b", false);
    m_fix_cmd_sync.test_repo_exists("src/test_a", true);
    m_fix_cmd_sync.test_repo_exists("src/test_a_b", true);
    m_fix_cmd_sync.test_repo_exists("src/test_b", true);

    m_fix_cmd_sync.sync({".", "src/commit_b"});

    m_fix_cmd_sync.test_basic_files();
}

} // namespace test

} // namespace exe

} // namespace repo

} // namespace esys
