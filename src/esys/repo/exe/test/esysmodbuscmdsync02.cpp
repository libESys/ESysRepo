/*!
 * \file esys/repo/exe/test/esysmodbuscmdsync02.cpp
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

/*! \class ESysModbusCmdSync02 esys/repo/exe/test/esysmodbuscmdsync02.cpp "esys/repo/exe/test/esysmodbuscmdsync02.cpp"
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(ESysModbusCmdSync02)
{
    FixCmd m_fix_cmd_sync;

    m_fix_cmd_sync.set_temp_sub_folder("esysmodbuscmdsync02");
    m_fix_cmd_sync.set_manifest_url("ssh://git@gitlab.com/libesys/esysmodbus/dev.git");

    m_fix_cmd_sync.init();
    m_fix_cmd_sync.sync();

    std::vector<std::string> paths = {".",
                                      "extlib/libmodbus",
                                      "extlib/matplotlib-cpp",
                                      "extlib/pyswig",
                                      "src/esysc",
                                      "src/esysfile",
                                      "src/esysmodbus",
                                      "src/esysmsvc",
                                      "src/esystest",
                                      "src/manifest"};

    for (auto &repo_path : paths) m_fix_cmd_sync.test_repo_exists(repo_path);
}

} // namespace test

} // namespace exe

} // namespace repo

} // namespace esys
