/*!
 * \file esys/repo/gitstats/test/basic01.cpp
 * \brief For precompiled headers
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2022 Michel Gillet
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
#include <esys/repo/gitstats/basic.h>

#include <boost/filesystem.hpp>

#include <iostream>
#include <vector>

namespace esys::repo::gitstats::test
{

namespace basic01
{

/*! \class Basic01 esys/repo/gitstats/test/basic01.cpp
 * "esys/repo/gitstats/test/basic01.cpp"
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(Basic01)
{
    boost::filesystem::path file_path;

    file_path = repo::test::TestCaseCtrl::get().GetTempFilesFolder();
    file_path /= ("basic01");

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

    libgit2::Git git;

    Result result = git.clone("https://gitlab.com/libesys/esysrepo/test_google_manifest.git",
                           file_path.normalize().make_preferred().string());
    if (result.error()) std::cout << "ERROR " << result << std::endl;
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);

    auto the_walk_commit = std::make_shared<Basic>();

    int result_int = git.walk_commits(the_walk_commit);
    ESYSTEST_REQUIRE_EQUAL(result_int, 0);

    result = git.close();
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);

    ESYSTEST_REQUIRE_EQUAL(the_walk_commit->get_data()->get_year_map().size(), 1);

    auto data_year = the_walk_commit->get_data()->get_year_map().begin()->second;
    ESYSTEST_REQUIRE_NE(data_year, nullptr);
    ESYSTEST_REQUIRE_EQUAL(data_year->get_year(), 2021);
    ESYSTEST_REQUIRE_EQUAL(data_year->get_weeks_with_data_count(), 3);

    std::vector<unsigned int> commit_counts = {1, 2, 1};
    std::vector<unsigned int> files_changed = {1, 2, 1};
    std::vector<unsigned int> insertions = {2, 14, 5};
    std::vector<unsigned int> deletions = {0, 0, 5};

    for (unsigned int week_idx = 0; week_idx < 3; ++week_idx)
    {
        auto data_week = data_year->get_weeks_with_data(week_idx);
        ESYSTEST_REQUIRE_NE(data_week, nullptr);
        ESYSTEST_REQUIRE_EQUAL(data_week->get_period_author_map().size(), 1);

        auto data_period_author = data_week->get_period_author_map().begin()->second;
        ESYSTEST_REQUIRE_NE(data_period_author, nullptr);

        ESYSTEST_REQUIRE_EQUAL(data_period_author->get_commit_count(), commit_counts[week_idx]);
        ESYSTEST_REQUIRE_EQUAL(data_period_author->get_files_changed(), files_changed[week_idx]);
        ESYSTEST_REQUIRE_EQUAL(data_period_author->get_line_added(), insertions[week_idx]);
        ESYSTEST_REQUIRE_EQUAL(data_period_author->get_line_removed(), deletions[week_idx]);
    }
}

} // namespace basic01

} // namespace esys::repo::gitstats::test
