/*!
 * \file esys/repo/exe/test/cmdsync08.cpp
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

namespace esys
{

namespace repo
{

namespace exe
{

namespace test
{

/*! \class CmdSync08 esys/repo/exe/test/cmdsync08.cpp "esys/repo/exe/test/cmdsync08.cpp"
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(CmdSync08)
{
    FixCmd m_fix_cmd_sync;

    m_fix_cmd_sync.set_temp_sub_folder("cmdsync08");
    m_fix_cmd_sync.set_manifest_url("ssh://git@gitlab.com/libesys/esysrepo/test_google_manifest.git");

    m_fix_cmd_sync.init();

    std::string branch = "commit_c";

    m_fix_cmd_sync.get_cmd_sync().set_branch(branch);
    m_fix_cmd_sync.sync();

    m_fix_cmd_sync.test_manifest_repo_head(branch);
    m_fix_cmd_sync.test_repo_exists("src/commit_c");
    m_fix_cmd_sync.test_repo_head("src/commit_c", branch);
}

} // namespace test

} // namespace exe

} // namespace repo

} // namespace esys
