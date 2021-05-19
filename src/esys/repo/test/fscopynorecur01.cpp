/*!
 * \file esys/repo/test/fscopynorecur01.cpp
 * \brief
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

#include <esys/repo/filesystem.h>

#include <boost/filesystem.hpp>

#include <iostream>

namespace esys
{

namespace repo
{

namespace test
{

/*! \class ConfigFileWrite01 esys/repo/test/fscopynorecur01.cpp "esys/repo/test/fscopynorecur01.cpp"
 *
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(FSCoypNoRecur01)
{
    boost::filesystem::path temp_path;
    boost::filesystem::path src_path;

    temp_path = repo::test::TestCaseCtrl::get().GetTempFilesFolder();
    temp_path /= ("fscoypnorecur01");

    src_path = repo::test::TestCaseCtrl::get().GetTestFilesFolder();

    bool remove_all = true;

    try
    {
        if (boost::filesystem::exists(temp_path)) boost::filesystem::remove_all(temp_path);
    }
    catch (const boost::filesystem::filesystem_error &e)
    {
        remove_all = false;
        std::cerr << e.what() << std::endl;
    }

    ESYSTEST_REQUIRE_EQUAL(remove_all, true);

    bool folder_created = boost::filesystem::create_directories(temp_path);
    ESYSTEST_REQUIRE_EQUAL(folder_created, true);

    int result = boost_no_recur::copy(src_path.string(), temp_path.string(), true);
    ESYSTEST_REQUIRE_EQUAL(result, 0);
}

} // namespace test

} // namespace repo

} // namespace esys
