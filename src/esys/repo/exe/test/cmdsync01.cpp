/*!
 * \file esys/repo/exe/test/cmdsync01.cpp
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

#include <esys/repo/libgit2/git.h>
#include <esys/repo/exe/cmdinit.h>
#include <esys/repo/exe/cmdsync.h>
#include <esys/repo/filesystem.h>

#include <filesystem>

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

    file_path = repo::test::TestCaseCtrl::get().GetTempFilesFolder();
    file_path /= ("cmdsync01");

    bool remove_all = true;

    try
    {
        if (boost::filesystem::exists(file_path)) boost_no_all::remove_all(file_path.string());
    }
    catch (const boost::filesystem::filesystem_error &e)
    {
        remove_all = false;
        std::cerr << e.what() << std::endl;
    }

    ESYSTEST_REQUIRE_EQUAL(remove_all, true);

    bool created = boost::filesystem::create_directory(file_path);
    ESYSTEST_REQUIRE_EQUAL(created, true);

    CmdInit cmd_init;
    auto git = std::make_shared<libgit2::Git>();

    cmd_init.set_url("https://gitlab.com/libesys/esysmodbus/manifest.git");
    cmd_init.set_parent_path(file_path.string());
    cmd_init.set_git(git);

    int result = cmd_init.run();
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    CmdSync cmd_sync;
    
    cmd_sync.set_parent_path(file_path.string());
    cmd_sync.set_git(git);

    result = cmd_sync.run();
    ESYSTEST_REQUIRE_EQUAL(result, 0);

}

} // namespace test

} // namespace exe

} // namespace repo

} // namespace esys
