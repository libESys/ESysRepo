/*!
 * \file esys/repo/libgit2/test/clonerepo02_libgit2.cpp
 * \brief For precompiled headers
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
#include <esys/repo/filesystem.h>

#include <boost/filesystem.hpp>

#include <iostream>

namespace esys
{

namespace repo
{

namespace libgit2
{

namespace test
{

/*! \class CloneRepo02LibGit2 esys/build/libgit2/test/clonerepo02_libgit2.cpp
 * "esys/build/libgit2/test/clonerepo02_libgit2.cpp"
 *
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(CloneRepo02LibGit2)
{
    boost::filesystem::path file_path;

    file_path = repo::test::TestCaseCtrl::get().GetTempFilesFolder();
    file_path /= ("clonerepo02libgit2");

    std::cout << "Temp folder = " << file_path << std::endl;

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

    Git git;

    int result =
        git.clone("ssh://git@gitlab.com/libesys/metacpp_manifest.git", file_path.normalize().make_preferred().string());
    if (result != 0) std::cout << "ERROR " << result << std::endl;
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    result = git.close();
    ESYSTEST_REQUIRE_EQUAL(result, 0);
}

} // namespace test

} // namespace libgit2

} // namespace repo

} // namespace esys
