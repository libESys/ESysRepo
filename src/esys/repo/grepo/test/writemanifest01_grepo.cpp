/*!
 * \file esys/repo/grepo/test/writemanifest01_grepo.cpp
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

    int result = data->add_location(location, true);
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    manifest.set_data(data);
    result = manifest.write(file_path.string());
    ESYSTEST_REQUIRE_EQUAL(result, 0);
}

} // namespace test

} // namespace grepo

} // namespace repo

} // namespace esys
