/*!
 * \file esys/repo/test/loadfolder01.cpp
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

#include <esys/repo/grepo/manifest.h>
#include <esys/repo/loadfolder.h>

#include <boost/filesystem.hpp>

#include <iostream>

namespace esys::repo::test
{

/*! \class LoadFolder01 esys/repo/test/loadfolder01.cpp "esys/repo/test/loadfolder01.cpp"
 *
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(LoadFolder01)
{
    boost::filesystem::path folder_path;

    folder_path = repo::test::TestCaseCtrl::get().GetTestFilesFolder();
    folder_path /= grepo::Manifest::get_folder_name();
    folder_path /= "repo01";

    LoadFolder load_folder;

    Result result = load_folder.run(folder_path.string());
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);

    auto manifest = load_folder.get_manifest();
    ESYSTEST_REQUIRE_NE(manifest, nullptr);

    auto locations = manifest->get_locations();
    ESYSTEST_REQUIRE_EQUAL(locations.size(), 2);

    auto loc_origin = manifest->find_location("origin");
    ESYSTEST_REQUIRE_NE(loc_origin, nullptr);
    ESYSTEST_REQUIRE_EQUAL(loc_origin->get_address(), "ssh://git@gitlab.com/libesys");

    auto loc_github = manifest->find_location("github");
    ESYSTEST_REQUIRE_NE(loc_github, nullptr);
    ESYSTEST_REQUIRE_EQUAL(loc_github->get_address(), "https://github.com");
}

} // namespace esys::repo::test
