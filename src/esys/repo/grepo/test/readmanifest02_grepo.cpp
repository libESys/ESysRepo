/*!
 * \file esys/repo/grepo/test/readmanifest02_grepo.cpp
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

#include <esys/repo/grepo/manifest.h>
#include <esys/repo/manifest/repository.h>

#include <boost/filesystem.hpp>

namespace esys
{

namespace repo
{

namespace grepo
{

namespace test
{

/*! \class ReadManifest02GRepo esys/repo/grepo/test/readmanifest02_grepo.cpp
 * "esys/repo/grepo/test/writemanifest02_grepo.cpp"
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(ReadManifest02GRepo)
{
    boost::filesystem::path file_path;

    file_path = repo::test::TestCaseCtrl::get().GetTestFilesFolder();
    file_path /= "grepo";
    file_path /= "default02.xml";

    Manifest manifest;

    int result = manifest.read(file_path.string());
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    auto data = manifest.get_data();
    ESYSTEST_REQUIRE_EQUAL(data->get_locations().size(), 3);
    ESYSTEST_REQUIRE_EQUAL(data->get_default_job_count(), 4);

    auto default_location = data->get_default_location();
    ESYSTEST_REQUIRE_NE(default_location, nullptr);
    ESYSTEST_REQUIRE_EQUAL(default_location->get_name(), "origin");
    ESYSTEST_REQUIRE_EQUAL(default_location->get_address(), "ssh://git@gitlab.com/libesys");
    ESYSTEST_REQUIRE_EQUAL(default_location, data->get_locations()[0]);

    ESYSTEST_REQUIRE_EQUAL(data->get_default_revision(), "refs/heads/master");

    std::vector<std::pair<std::string, std::string>> origin_repos = {
        {"esysos", "src/esysos"},
        {"esysdep", "src/esysdep"},
        {"esysfile", "src/esysfile"},
        {"esysres", "src/esysres"},
    };

    std::vector<std::pair<std::string, std::string>> gerrit_repos = {
        {"esys", "src/esys"},
        {"esysdoc", "src/esysdoc"},
        {"esyssdk", "src/esyssdk"},
        {"esysboard", "src/esysboard"},
        {"esysboot", "src/esysboot"},
        {"esysbuild", "src/esysbuild"},
        {"esyscontrib", "src/esyscontrib"},
        {"esyscore", "src/esyscore"},
        {"esysdev", "."},
        {"esysio", "src/esysio"},
        {"esyslog", "src/esyslog"},
        {"esysprog", "src/esysprog"},
        {"esysproj", "src/esysproj"},
        {"esysrpc", "src/esysrpc"},
        {"esystest", "src/esystest"},
        {"esystools", "src/esystools"},
        {"esysui", "src/esysui"},
        {"esysiss", "src/esysiss"},
        {"esyspytools", "src/esyspytools"},
        {"esysnet", "src/esysnet"},
        {"esyscrypto", "src/esyscrypto"},
        {"esysbuildsdk", "src/esysbuildsdk"},
        {"esysmanifest", "src/esysmanifest"},
        {"dfuprog", "src/dfuprog"},
    };

    std::vector<std::pair<std::string, std::string>> extlib_repos = {
        {"esysc", "src/esysc"},
        {"arduino1710", "extlib/arduino1710"},
        {"asf", "extlib/asf"},
        {"boost_process", "extlib/boost_process"},
        {"cleware", "extlib/cleware"},
        {"ctb", "extlib/ctb"},
        {"dbg_log", "extlib/dbg_log"},
        {"freertosv812", "extlib/freertosv812"},
        {"freertosv1000", "extlib/freertos"},
        {"git_hooks", "extlib/git_hooks"},
        {"mysystemc-231", "extlib/mysystemc-231"},
        {"mysystemc-232", "extlib/mysystemc-232"},
        {"stm32", "extlib/stm32"},
        {"stm32l4", "extlib/stm32l4"},
        {"stm32f7", "extlib/stm32f7"},
        {"stm32f4", "extlib/stm32f4"},
        {"stm32f1", "extlib/stm32f1"},
        {"stm32f0", "extlib/stm32f0"},
        {"stm32h7", "extlib/stm32h7"},
        {"pyswig", "extlib/pyswig"},
        {"segger_rtt", "extlib/segger_rtt"},
        {"cryptoauthlib", "extlib/cryptoauthlib"},
    };

    auto test_fct = [](std::vector<std::pair<std::string, std::string>> &values,
                       std::shared_ptr<manifest::Location> location) {
        ESYSTEST_REQUIRE_EQUAL(values.size(), location->get_repos().size());

        for (std::size_t idx = 0; idx < values.size(); ++idx)
        {
            auto repo = location->get_repos()[idx];

            ESYSTEST_REQUIRE_EQUAL(repo->get_name(), values[idx].first);
            ESYSTEST_REQUIRE_EQUAL(repo->get_path(), values[idx].second);
        }
    };

    test_fct(origin_repos, data->get_locations()[0]);
    test_fct(gerrit_repos, data->get_locations()[1]);
    test_fct(extlib_repos, data->get_locations()[2]);
}

} // namespace test

} // namespace grepo

} // namespace repo

} // namespace esys
