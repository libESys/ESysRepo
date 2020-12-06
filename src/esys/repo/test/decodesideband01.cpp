/*!
 * \file esys/repo/test/decodesideband01.cpp
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

#include <esys/repo/gitbase.h>

#include <boost/filesystem.hpp>

#include <iostream>

namespace esys
{

namespace repo
{

namespace test
{

/*! \class DecodeSideband01 esys/repo/test/decodesideband01.cpp
 * "esys/repo/test/decodesideband01.cpp"
 *
 *  \brief
 *
 */
ESYSTEST_AUTO_TEST_CASE(DecodeSideband01)
{
    boost::filesystem::path file_path;

    file_path = repo::test::TestCaseCtrl::get().GetTempFilesFolder();
    file_path /= ("processsideband01");

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

    std::vector<std::string> inputs;
    std::string base_input;
    std::string input1;
    git::Progress progress;
    int result;

    auto build_test_vec = [](const std::string &input, std::vector<std::string> &inputs) {
        inputs = {input, input + "\r", input + "\n", input + "\r\n", input + "\n\r"};
    };

    base_input = "Enumerating objects: 6, done.";
    build_test_vec(base_input, inputs);

    for (auto &input : inputs)
    {
        result = GitBase::decode_sideband_progress(input, progress);
        ESYSTEST_REQUIRE_EQUAL(result, 0);
        ESYSTEST_REQUIRE_EQUAL(progress.get_fetch_step(), git::FetchStep::ENUMERATING);
        ESYSTEST_REQUIRE_EQUAL(progress.get_done(), true);
        ESYSTEST_REQUIRE_EQUAL(progress.get_percentage(), -1);
    }

    base_input = "Counting objects:  16% (1/6)";
    build_test_vec(base_input, inputs);

    for (auto &input : inputs)
    {
        result = GitBase::decode_sideband_progress(input, progress);
        ESYSTEST_REQUIRE_EQUAL(result, 0);
        ESYSTEST_REQUIRE_EQUAL(progress.get_fetch_step(), git::FetchStep::COUNTING);
        ESYSTEST_REQUIRE_EQUAL(progress.get_done(), false);
        ESYSTEST_REQUIRE_EQUAL(progress.get_percentage(), 16);
    }

    base_input = "counting objects:  33% (2/6)\rcounting objects:  50% (3/6)\n";
    build_test_vec(base_input, inputs);

    for (auto &input : inputs)
    {
        result = GitBase::decode_sideband_progress(input, progress);
        ESYSTEST_REQUIRE_EQUAL(result, 0);
        ESYSTEST_REQUIRE_EQUAL(progress.get_fetch_step(), git::FetchStep::COUNTING);
        ESYSTEST_REQUIRE_EQUAL(progress.get_done(), false);
        ESYSTEST_REQUIRE_EQUAL(progress.get_percentage(), 50);
    }

    base_input = "counting objects:  66% (4/6)";
    build_test_vec(base_input, inputs);

    for (auto &input : inputs)
    {
        result = GitBase::decode_sideband_progress(input, progress);
        ESYSTEST_REQUIRE_EQUAL(result, 0);
        ESYSTEST_REQUIRE_EQUAL(progress.get_fetch_step(), git::FetchStep::COUNTING);
        ESYSTEST_REQUIRE_EQUAL(progress.get_done(), false);
        ESYSTEST_REQUIRE_EQUAL(progress.get_percentage(), 66);
    }

    base_input = "counting objects:  83% (5/6)\rcounting objects: 100% (6/6)\rcounting objects: 100% (6/6), done.";
    build_test_vec(base_input, inputs);

    for (auto &input : inputs)
    {
        result = GitBase::decode_sideband_progress(input, progress);
        ESYSTEST_REQUIRE_EQUAL(result, 0);
        ESYSTEST_REQUIRE_EQUAL(progress.get_fetch_step(), git::FetchStep::COUNTING);
        ESYSTEST_REQUIRE_EQUAL(progress.get_done(), true);
        ESYSTEST_REQUIRE_EQUAL(progress.get_percentage(), 100);
    }

    base_input =
        "counting objects:  83% (5/6)\rcounting objects: 100% (6/6)\rcounting objects: 100% (6/6), done.\rcompressing "
        "objects:  25% (1/4)\n";
    build_test_vec(base_input, inputs);
    for (auto &input : inputs)
    {
        result = GitBase::decode_sideband_progress(input, progress);
        ESYSTEST_REQUIRE_EQUAL(result, 0);
        ESYSTEST_REQUIRE_EQUAL(progress.get_fetch_step(), git::FetchStep::COMPRESSING);
        ESYSTEST_REQUIRE_EQUAL(progress.get_done(), false);
        ESYSTEST_REQUIRE_EQUAL(progress.get_percentage(), 25);
    }
}

} // namespace test

} // namespace repo

} // namespace esys
