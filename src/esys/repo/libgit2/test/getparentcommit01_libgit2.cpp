/*!
 * \file esys/repo/libgit2/test/getparentcommit01_libgit2.cpp
 * \brief For precompiled headers
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

#include <esys/repo/libgit2/git.h>

#include <libssh2.h>

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

/*! \class GetParentCommit01LibGit2 esys/repo/libgit2/test/getparentcommit01_libgit2.cpp
 * "esys/repo/libgit2/test/getparentcommit01_libgit2.cpp"
 *
 *  \brief
 *
 */
ESYSTEST_AUTO_TEST_CASE(GetParantCommit01LibGit2)
{
    auto &ctrl = repo::test::TestCaseCtrl::get();

    boost::filesystem::path file_path = ctrl.delete_create_temp_folder("getparantcommit01libgit2");
    ESYSTEST_REQUIRE_EQUAL(file_path.string().empty(), false);

    Git git;

    Result result =
        git.clone("ssh://git@gitlab.com/libesys/esysrepo/test.git", file_path.normalize().make_preferred().string());
    if (result.error()) std::cout << "ERROR " << result << std::endl;
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);

    result = git.checkout("branch_a_b");
    if (result.error()) std::cout << "ERROR " << result << std::endl;
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);

    git::CommitHash last_commit;
    git::CommitHash parent_commit;

    int result_int = git.get_last_commit(last_commit);
    if (result_int != 0) std::cout << "ERROR " << result << std::endl;
    ESYSTEST_REQUIRE_EQUAL(result_int, 0);
    ESYSTEST_REQUIRE_EQUAL(last_commit.get_hash(), "9200c176d27a1ecb7d35edffc90b4a452e3902a8");

    result_int = git.get_parent_commit(last_commit, parent_commit);
    if (result_int != 0) std::cout << "ERROR " << result << std::endl;
    ESYSTEST_REQUIRE_EQUAL(result_int, 0);
    ESYSTEST_REQUIRE_EQUAL(parent_commit.get_hash(), "3a1c73ade6f3bd5112d9ae993d83612c1a4d85b2");

    result_int = git.get_parent_commit(last_commit, parent_commit, 2);
    if (result_int != 0) std::cout << "ERROR " << result << std::endl;
    ESYSTEST_REQUIRE_EQUAL(result_int, 0);
    ESYSTEST_REQUIRE_EQUAL(parent_commit.get_hash(), "64280d3bed1531db5965fca8183cb68ad3770659");

    result_int = git.get_parent_commit(last_commit, parent_commit, 3);
    if (result_int != 0) std::cout << "ERROR " << result << std::endl;
    ESYSTEST_REQUIRE_EQUAL(result_int, 0);
    ESYSTEST_REQUIRE_EQUAL(parent_commit.get_hash(), "edc6451103785867926c6dd67a7299c3c531234b");

    result = git.close();
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);
}

} // namespace test

} // namespace libgit2

} // namespace repo

} // namespace esys
