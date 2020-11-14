/*!
 * \file esys/repo/manifest/test/xmlfilewrite01_manifest.cpp
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

#include <esys/repo/manifest/xmlfile.h>

#include <boost/filesystem.hpp>

#include <iostream>

namespace esys
{

namespace repo
{

namespace manifest
{

namespace test
{

/*! \class XMLFileWrite01Manifest esys/repo/manifest/test/xmlfilewrite01_manifest.cpp
 * "esys/repo/manifest/test/xmlfilewrite01_manifest.cpp"
 *
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(XMLFileWrite01Manifest)
{
    boost::filesystem::path path;

    path = repo::test::TestCaseCtrl::get().GetTempFilesFolder();
    path /= ("xmlfilewrite01manifest");

    bool remove_all = true;

    try
    {
        if (boost::filesystem::exists(path)) boost::filesystem::remove_all(path);
    }
    catch (const boost::filesystem::filesystem_error &e)
    {
        remove_all = false;
        std::cerr << e.what() << std::endl;
    }

    ESYSTEST_REQUIRE_EQUAL(remove_all, true);

    bool folder_created = boost::filesystem::create_directories(path);
    ESYSTEST_REQUIRE_EQUAL(folder_created, true);

    XMLFile xml_file;
    std::shared_ptr<Manifest> manifest = std::make_shared<Manifest>();
    std::shared_ptr<manifest::Location> location;
    std::shared_ptr<manifest::Repository> repo;
    
    std::vector<std::pair<std::string, std::string>> origin_repos = {
        {"esysos", "src/esysos"},
        {"esysdep", "src/esysdep"},
        {"esysfile", "src/esysfile"},
        {"esysres", "src/esysres"},
    };

    location = std::make_shared<manifest::Location>("origin", "ssh://git@gitlab.com/libesys");

    for (auto &repo_cfg : origin_repos)
    {
        location->add_repo(repo_cfg.first, repo_cfg.second);
    }

    manifest->add_location(location);

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

    location = std::make_shared<manifest::Location>("gerrit", "ssh://git@gitlab.com/libesys/gerrit");

    for (auto &repo_cfg : gerrit_repos)
    {
        location->add_repo(repo_cfg.first, repo_cfg.second);
    }

    manifest->add_location(location);

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

    location = std::make_shared<manifest::Location>("extlib", "ssh://git@gitlab.com/libesys/extlib");

    for (auto &repo_cfg : extlib_repos)
    {
        location->add_repo(repo_cfg.first, repo_cfg.second);
    }

    manifest->add_location(location);

    xml_file.set_manifest(manifest);

    path /= ".esysrepo.manifest.xml";

    int result = xml_file.write(path.make_preferred().string());
    ESYSTEST_REQUIRE_EQUAL(result, 0);
}

}

} // namespace test

} // namespace repo

} // namespace esys
