/*!
 * \file esys/repo/libgit2/test/getstatus01_libgit2.cpp
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
#include <esys/repo/filesystem.h>

#include <boost/filesystem.hpp>

#include <fstream>
#include <iostream>

namespace esys
{

namespace repo
{

namespace libgit2
{

namespace test
{

/*! \class GetStatus01LibGit2 esys/repo/libgit2/test/getstatus01_libgit2.cpp
 * "esys/repo/libgit2/test/getstatus01_libgit2.cpp"
 *
 * \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(GetStatus01LibGit2)
{
    boost::filesystem::path file_path;

    file_path = repo::test::TestCaseCtrl::get().GetTempFilesFolder();
    file_path /= ("getstatus01libgit2");

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

    Result result =
        git.clone("https://gitlab.com/libesys/esysmodbus/dev.git", file_path.normalize().make_preferred().string());
    if (result.error()) std::cout << "ERROR " << result << std::endl;
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);

    boost::filesystem::path new_file_path = file_path;
    new_file_path /= "new_file.txt";
    std::ofstream nf(new_file_path.string());

    nf << "Noting special" << std::endl;
    nf.close();

    boost::filesystem::path old_file_path = file_path;
    old_file_path /= "README.md";

    std::ofstream f(old_file_path.string(), std::ios_base::app);
    ESYSTEST_REQUIRE_EQUAL(f.is_open(), true);

    f << "Append some silly text" << std::endl;
    f.close();

    git::RepoStatus repo_status;

    result = git.get_status(repo_status);
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);

    ESYSTEST_REQUIRE_EQUAL(repo_status.get_all().size(), 2);
    ESYSTEST_REQUIRE_EQUAL(repo_status.get_head_to_index().size(), 0);
    ESYSTEST_REQUIRE_EQUAL(repo_status.get_index_to_work_dir().size(), 2);

    result = git.close();
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);
}

} // namespace test

} // namespace libgit2

} // namespace repo

} // namespace esys
