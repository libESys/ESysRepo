/*!
 * \file esys/repo/grepo/test/readmanifest01_grepo.cpp
 * \brief For precompiled headers
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2021 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See
 * accompanying file LICENSE_3_1.txt or
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

/*! \class ReadManifest01GRepo esys/repo/grepo/test/readmanifest01_grepo.cpp
 * "esys/repo/grepo/test/writemanifest01_grepo.cpp"
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(ReadManifest01GRepo)
{
    boost::filesystem::path file_path;

    file_path = repo::test::TestCaseCtrl::get().GetTestFilesFolder();
    file_path /= "grepo";
    file_path /= "default01.xml";

    Manifest manifest;

    int result = manifest.read(file_path.string());
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    auto data = manifest.get_data();
    ESYSTEST_REQUIRE_EQUAL(data->get_locations().size(), 1);
    ESYSTEST_REQUIRE_EQUAL(data->get_locations()[0]->get_repos().size(), 8);
    ESYSTEST_REQUIRE_EQUAL(data->get_default_job_count(), 4);

    auto default_location = data->get_default_location();
    ESYSTEST_REQUIRE_NE(default_location, nullptr);
    ESYSTEST_REQUIRE_EQUAL(default_location->get_name(), "origin");
    ESYSTEST_REQUIRE_EQUAL(default_location->get_address(), "ssh://git@gitlab.com/libesys/");
    ESYSTEST_REQUIRE_EQUAL(default_location, data->get_locations()[0]);

    ESYSTEST_REQUIRE_EQUAL(data->get_default_revision(), "refs/heads/master");

    std::vector<std::pair<std::string, std::string>> repos = {{"esysbuild/dev", "."},
                                                              {"esysbuild/esysbuild", "src/esysbuild"},
                                                              {"esysrepo/esysrepo", "src/esysrepo"},
                                                              {"extlib/pyswig", "extlib/pyswig"},
                                                              {"esysfile", "src/esysfile"},
                                                              {"esystest", "src/esystest"},
                                                              {"esys_cmake_scripts", "src/esys_cmake_scripts"},
                                                              {"esysmsvc", "src/esysmsvc"}};

    for (std::size_t idx = 0; idx < default_location->get_repos().size(); ++idx)
    {
        auto repo = default_location->get_repos()[idx];

        ESYSTEST_REQUIRE_EQUAL(repo->get_name(), repos[idx].first);
        ESYSTEST_REQUIRE_EQUAL(repo->get_path(), repos[idx].second);
    }
}

} // namespace test

} // namespace grepo

} // namespace repo

} // namespace esys
