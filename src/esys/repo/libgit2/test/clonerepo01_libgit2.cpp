/*!
 * \file esys/repo/libgit2/test/clonerepo01_libgit2.cpp
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

/*! \class CloneRepo01LibGit2 esys/build/libgit2/test/clonerepo01_libgit2.cpp
 * "esys/build/libgit2/test/clonerepo01_libgit2.cpp"
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(CloneRepo01LibGit2)
{
    boost::filesystem::path file_path;

    file_path = repo::test::TestCaseCtrl::get().GetTempFilesFolder();
    file_path /= ("clonerepo01libgit2");

    bool remove_all = true;

    try
    {
        if (boost::filesystem::exists(file_path)) boost::filesystem::remove_all(file_path);
    }
    catch (const boost::filesystem::filesystem_error &e)
    {
        remove_all = false;
        std::cerr << e.what() << std::endl;
    }

    ESYSTEST_REQUIRE_EQUAL(remove_all, true);

    Git git;

    int result = git.clone("https://gitlab.com/libesys/esystest.git", file_path.normalize().make_preferred().string());
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    /*std::vector<git::Remote> remotes;
    result = git.get_remotes(remotes);
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    std::vector<git::Branch> branches;
    result = git.get_branches(branches, git::BranchType::LOCAL);
    ESYSTEST_REQUIRE_EQUAL(result, 0); */

    result = git.close();
    ESYSTEST_REQUIRE_EQUAL(result, 0);
}

} // namespace test

} // namespace libgit2

} // namespace repo

} // namespace esys
