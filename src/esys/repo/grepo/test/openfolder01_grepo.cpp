/*!
 * \file esys/repo/grepo/test/openfolder01_grepo.cpp
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

#include <esys/repo/grepo/folder.h>
#include <esys/repo/grepo/manifest.h>
#include <esys/repo/manifest/repository.h>

#include <boost/filesystem.hpp>

namespace esys::repo::grepo::test
{

/*! \class ReadManifest01GRepo esys/repo/grepo/test/openfolder01_grepo.cpp
 * "esys/repo/grepo/test/openfolder01_grepo.cpp"
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(OpenFolder01GRepo)
{
    boost::filesystem::path file_path;
    boost::filesystem::path manifest_path;

    file_path = repo::test::TestCaseCtrl::get().GetTestFilesFolder();
    file_path /= grepo::Manifest::get_folder_name();
    file_path /= "repo01";

    manifest_path = file_path;
    manifest_path /= ".repo";
    manifest_path /= "manifests";
    manifest_path /= "default.xml";

    Folder folder;

    int result = folder.open(file_path.string());
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    auto config = folder.get_config();
    ESYSTEST_REQUIRE_NE(config, nullptr);

    ESYSTEST_REQUIRE_EQUAL(config->get_manifest_path(), manifest_path.string());
}

} // namespace esys::repo::grepo::test
