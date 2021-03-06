/*!
 * \file esys/repo/grepo/test/writemanifest01_grepo.cpp
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

#include <boost/filesystem.hpp>

namespace esys
{

namespace repo
{

namespace grepo
{

namespace test
{

/*! \class WriteManifest01GRepo esys/repo/grepo/test/writemanifest01_grepo.cpp
 * "esys/repo/grepo/test/writemanifest01_grepo.cpp"
 *  \brief
 *
 */
ESYSTEST_AUTO_TEST_CASE(WriteManifest01GRepo)
{
    boost::filesystem::path file_path;

    file_path = repo::test::TestCaseCtrl::get().GetTempFilesFolder();
    file_path /= ("write_grepo_manifest.xml");

    Manifest manifest;
    auto data = std::make_shared<repo::Manifest>();
    auto location = std::make_shared<manifest::Location>("origin", "ssh://git@gitlab.com/libesys");
    auto repo = location->add_repo("esysbuild/dev", ".");

    repo = location->add_repo("esysbuild/esysbuild", "src/esysbuild");

    repo = location->add_repo("esysrepo/esysrepo", "src/esysrepo");

    repo = location->add_repo("extlib/pyswig", "extlib/pyswig");

    repo = location->add_repo("esysfile", "src/esysfile");

    int result_int = data->add_location(location, true);
    ESYSTEST_REQUIRE_EQUAL(result_int, 0);

    manifest.set_data(data);
    Result result = manifest.write(file_path.string());
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);
}

} // namespace test

} // namespace grepo

} // namespace repo

} // namespace esys
