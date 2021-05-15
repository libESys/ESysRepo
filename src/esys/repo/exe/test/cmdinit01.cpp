/*!
 * \file esys/repo/exe/test/cmdinit01.cpp
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

/*! \class CmdInit01 esys/repo/exe/test/cmdinit01.cpp
 * "esys/repo/exe/test/cmdinit01.cpp"
 *
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(CmdInit01)
{
    boost::filesystem::path file_path;

    auto &ctrl = repo::test::TestCaseCtrl::get();
    file_path = ctrl.delete_create_temp_folder("cmdinit01");
    ESYSTEST_REQUIRE_EQUAL(file_path.string().empty(), false);

    auto logger = ctrl.get_logger("logger", file_path.string());
    ESYSTEST_REQUIRE_NE(logger, nullptr);

    CmdInit cmd_init;
    auto git = std::make_shared<libgit2::Git>();
    git->set_logger_if(logger);

    file_path /= "manifest";
    cmd_init.set_url("https://gitlab.com/libesys/esysmodbus/manifest.git");
    cmd_init.set_parent_path(file_path.string());
    cmd_init.set_git(git);
    cmd_init.set_logger_if(logger);

    int result = cmd_init.run();
    ESYSTEST_REQUIRE_EQUAL(result, 0);
}

} // namespace test

} // namespace exe

} // namespace repo

} // namespace esys
