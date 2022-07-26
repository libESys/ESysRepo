/*!
 * \file esys/repo/test/resultcode01.cpp
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

#include <esys/repo/resultcode.h>

#include <iostream>

namespace esys::repo::test
{

/*! \class ResultCode01 esys/repo/test/resultcode01.cpp "esys/repo/test/resultcode01.cpp"
 *
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(ResultCode01)
{
    ESYSTEST_REQUIRE_NE(ResultCode::s_get_ints().size(), 0);

    for (auto id : ResultCode::s_get_ints())
    {
        std::cout << id << " = " << ResultCode::s_find_name(id) << std::endl;
    }
}

} // namespace esys::repo::test
