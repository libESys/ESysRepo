/*!
 * \file esys/repo/cli/test/app01.cpp
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

#include <iostream>

namespace esys
{

namespace repo
{

namespace cli
{

namespace test
{

/*! \class App01 esys/repo/cli/test/app01.cpp
 * "esys/repo/cli/test/app01.cpp"
 *
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(App01)
{
    boost::filesystem::path file_path;

    auto &ctrl = repo::test::TestCaseCtrl::get();
    file_path = ctrl.delete_create_temp_folder("app01");
    ESYSTEST_REQUIRE_EQUAL(file_path.string().empty(), false);

    std::string url = "https://gitlab.com/libesys/esysmodbus/manifest.git";
    std::vector<std::string> args;
    int result = 0;

    {
        App app;

        std::cout << "App 1" << std::endl;
        std::cout << "===========" << std::endl;

        args = {};
        app.set_args(args);
        result = app.parse_and_configure();
        ESYSTEST_REQUIRE_NE(result, 0);

        args = {"init", "-u", url, "--folder", file_path.string()};
        app.set_args(args);
        result = app.parse_and_configure();
        ESYSTEST_REQUIRE_EQUAL(result, 0);
        ESYSTEST_REQUIRE_EQUAL(app.get_cmd_init().get_cmd().get_url(), url);

        result = app.run();
        ESYSTEST_REQUIRE_EQUAL(result, 0);
    }

    {
        App app;

        std::cout << "App 2" << std::endl;
        std::cout << "===========" << std::endl;

        args = {"sync", "-j", "4", "--folder", file_path.string()};
        app.set_args(args);
        result = app.parse_and_configure();
        ESYSTEST_REQUIRE_EQUAL(result, 0);

        result = app.run();
        ESYSTEST_REQUIRE_EQUAL(result, 0);
    }

    {
        App app;

        std::cout << "App 3" << std::endl;
        std::cout << "===========" << std::endl;

        args = {"info", "--folder", file_path.string()};
        app.set_args(args);
        result = app.parse_and_configure();
        ESYSTEST_REQUIRE_EQUAL(result, 0);

        result = app.run();
        ESYSTEST_REQUIRE_EQUAL(result, 0);
    }

    {
        App app;

        std::cout << "App 4" << std::endl;
        std::cout << "===========" << std::endl;

        args = {"list", "--folder", file_path.string()};
        app.set_args(args);
        result = app.parse_and_configure();
        ESYSTEST_REQUIRE_EQUAL(result, 0);

        result = app.run();
        ESYSTEST_REQUIRE_EQUAL(result, 0);
    }

    {
        App app;

        std::cout << "App 5" << std::endl;
        std::cout << "===========" << std::endl;

        args = {"manifest", "--folder", file_path.string()};
        app.set_args(args);
        result = app.parse_and_configure();
        ESYSTEST_REQUIRE_EQUAL(result, 0);

        result = app.run();
        ESYSTEST_REQUIRE_EQUAL(result, 0);
    }

    {
        App app;

        std::cout << "App 6" << std::endl;
        std::cout << "===========" << std::endl;

        args = {"status", "--folder", file_path.string()};
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
