/*!
 * \file esys/repo/manifest/test/xmlfileread01_manifest.cpp
 * \brief For precompiled headers
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2022 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/test/esysrepo_t_prec.h"

#include <esys/repo/manifest/xmlfile.h>
#include <esys/repo/manifest/repository.h>

#include <boost/filesystem.hpp>

#include <iostream>

namespace esys::repo::manifest::test
{

/*! \class XMLFileRead01Manifest esys/repo/manifest/test/xmlfileread01_manifest.cpp
 * "esys/repo/manifest/test/xmlfileread01_manifest.cpp"
 *
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(XMLFileRead01Manifest)
{
    boost::filesystem::path path;

    path = repo::test::TestCaseCtrl::get().GetTestFilesFolder();
    path /= "manifest";
    path /= "manifest01.xml";

    XMLFile xml_file;
    std::shared_ptr<Manifest> manifest = std::make_shared<Manifest>();
    std::shared_ptr<manifest::Location> location;
    std::shared_ptr<manifest::Repository> repo;

    ESYSTEST_REQUIRE_EQUAL(boost::filesystem::exists(path), true);
    Result result = xml_file.read(path.string());
    if (result.error())
    {
        std::cout << "ERROR : result = " << result << std::endl;
        int err_idx = 0;

        if (xml_file.get_errors().size() == 0)
            std::cout << "No error logged." << std::endl;
        else
        {
            for (auto err : xml_file.get_errors())
            {
                std::cout << "[" << err_idx << "]" << std::endl;
                std::cout << "    value = " << err->get_value() << std::endl;
                std::cout << "    msg = " << err->get_msg() << std::endl << std::endl;
            }
        }
    }
    else
        std::cout << "No read error." << std::endl;

    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);
    ESYSTEST_REQUIRE_NE(xml_file.get_data(), nullptr);

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

    std::vector<std::pair<std::string, std::string>> origin_repos = {
        {"esysos", "src/esysos"},
        {"esysdep", "src/esysdep"},
        {"esysfile", "src/esysfile"},
        {"esysres", "src/esysres"},
    };

    location = xml_file.get_data()->find_location("origin");
    ESYSTEST_REQUIRE_NE(location, nullptr);
    test_fct(origin_repos, location);
    ESYSTEST_REQUIRE_EQUAL(location->get_address(), "ssh://git@gitlab.com/libesys");
    ESYSTEST_REQUIRE_EQUAL(location->get_alt_address(), "https://gitlab.com/libesys");

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

    location = xml_file.get_data()->find_location("gerrit");
    ESYSTEST_REQUIRE_NE(location, nullptr);
    test_fct(gerrit_repos, location);
    ESYSTEST_REQUIRE_EQUAL(location->get_address(), "ssh://git@gitlab.com/libesys/gerrit");
    ESYSTEST_REQUIRE_EQUAL(location->get_alt_address(), "https://gitlab.com/libesys/gerrit");

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

    location = xml_file.get_data()->find_location("extlib");
    ESYSTEST_REQUIRE_NE(location, nullptr);
    test_fct(extlib_repos, location);
    ESYSTEST_REQUIRE_EQUAL(location->get_address(), "ssh://git@gitlab.com/libesys/extlib");
    ESYSTEST_REQUIRE_EQUAL(location->get_alt_address(), "https://gitlab.com/libesys/extlib");

    auto &groups = xml_file.get_data()->get_groups();
    ESYSTEST_REQUIRE_EQUAL(groups.get_groups().size(), 2);

    std::vector<std::pair<std::string, std::vector<std::string>>> group_defs = {
        {"vhw", {"src/esys", "src/esysc"}}, {"hw", {"extlib/stm32h7", "extlib/segger_rtt"}}};

    for (std::size_t idx = 0; idx < group_defs.size(); ++idx)
    {
        auto group_def = group_defs[idx];
        auto group = groups.get_groups()[idx];
        ESYSTEST_REQUIRE_EQUAL(group_def.first, group->get_name());
        ESYSTEST_REQUIRE_EQUAL(group_def.second.size(), group->get_repos().size());
        for (std::size_t repo_idx = 0; repo_idx < group_def.second.size(); ++repo_idx)
            ESYSTEST_REQUIRE_EQUAL(group_def.second[repo_idx], group->get_repos()[repo_idx]->get_path());
    }
}

} // namespace esys::repo::manifest::test
