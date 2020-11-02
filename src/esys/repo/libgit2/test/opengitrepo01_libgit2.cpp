/*!
 * \file esys/repo/libgit2/test/opengitrepo01_libgit2.cpp
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

namespace esys
{

namespace repo
{

namespace libgit2
{

namespace test
{

/*! \class OpenGitRepo01LibGit2 esys/build/libgit2/test/opengitrepo01_libgit2.cpp
 * "esys/build/libgit2/test/opengitrepo01_libgit2.cpp"
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(OpenGitRepo01LibGit2)
{
    boost::filesystem::path file_path;

    file_path = repo::test::TestCaseCtrl::get().GetTestFilesFolder();
    file_path /= ("../../.git");

    file_path = "C:\\project\\libesys\\esysbuild_manifest";
    Git git;

    int result = git.open(file_path.normalize().make_preferred().string());
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    std::vector<git::Remote> remotes;
    result = git.get_remotes(remotes);
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    std::vector<git::Branch> branches;
    result = git.get_branches(branches, git::BranchType::LOCAL);
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    result = git.close();
    ESYSTEST_REQUIRE_EQUAL(result, 0);
}

} // namespace test

} // namespace libgit2

} // namespace repo

} // namespace esys
