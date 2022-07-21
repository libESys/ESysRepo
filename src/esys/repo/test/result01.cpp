/*!
 * \file esys/repo/test/result01.cpp
 * \brief
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

#include <esys/repo/result.h>

#include <boost/filesystem.hpp>

namespace esys::repo::test
{

Result fct_a()
{
    return ESYSREPO_RESULT(ResultCode::SUCCESS);
}

Result fct_b()
{
    return ESYSREPO_RESULT(ResultCode::GENERIC_ERROR);
}

Result fct_c()
{
    Result result = fct_b();

    return ESYSREPO_RESULT(result);
}

namespace result01
{

/*! \class Result01 esys/repo/test/result01.cpp "esys/repo/test/result01.cpp"
 *
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(Result01)
{
    auto result = fct_a();

    ESYSTEST_REQUIRE_EQUAL(result.success(), true);
    ESYSTEST_REQUIRE_EQUAL(result.error(), false);
    ESYSTEST_REQUIRE_EQUAL(result, ResultCode::SUCCESS);
    ESYSTEST_REQUIRE_EQUAL(result.get_error_info(), nullptr);

    result = fct_b();
    ESYSTEST_REQUIRE_EQUAL(result.success(), false);
    ESYSTEST_REQUIRE_EQUAL(result.error(), true);
    ESYSTEST_REQUIRE_EQUAL(result, ResultCode::GENERIC_ERROR);
    ESYSTEST_REQUIRE_NE(result.get_error_info(), nullptr);
    ESYSTEST_REQUIRE_EQUAL(result.get_error_info()->get_line_number(), 34);

    boost::filesystem::path path = result.get_error_info()->get_file();
    ESYSTEST_REQUIRE_EQUAL(path.filename(), "result01.cpp");

    result = fct_c();
    ESYSTEST_REQUIRE_EQUAL(result.success(), false);
    ESYSTEST_REQUIRE_EQUAL(result.error(), true);
    ESYSTEST_REQUIRE_EQUAL(result, ResultCode::GENERIC_ERROR);
    ESYSTEST_REQUIRE_NE(result.get_error_info(), nullptr);
    ESYSTEST_REQUIRE_EQUAL(result.get_error_info()->get_line_number(), 41);

    std::shared_ptr<ErrorInfo> error_info = result.get_error_info()->get_prev();
    ESYSTEST_REQUIRE_NE(error_info, nullptr);
    ESYSTEST_REQUIRE_EQUAL(error_info->get_line_number(), 34);
    ESYSTEST_REQUIRE_EQUAL(error_info->get_prev(), nullptr);

}

} // namespace result01

} // namespace esys::repo::test
