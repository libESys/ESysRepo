/*!
 * \file esys/repo/cli/test/app02.cpp
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

#include <esys/repo/cli/app.h>

namespace esys
{

namespace repo
{

namespace cli
{

namespace test
{

/*! \class App02 esys/repo/cli/test/app02.cpp "esys/repo/cli/test/app02.cpp"
 *
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(App02)
{
    std::vector<std::string> args;
    int result = 0;

    {
        App app;

        args = {};
        app.set_args(args);
        result = app.parse_and_configure();
        ESYSTEST_REQUIRE_NE(result, 0);

        args = {"version"};
        app.set_args(args);
        result = app.parse_and_configure();
        ESYSTEST_REQUIRE_EQUAL(result, 0);

        result = app.run();
        ESYSTEST_REQUIRE_EQUAL(result, 0);
    }
}

} // namespace test

} // namespace cli

} // namespace repo

} // namespace esys
