/*!
 * \file esys/repo/grepo/test/find_path_by_repo01_grepo.cpp
 * \brief For precompiled headers
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
#include <esys/repo/manifest/repository.h>

#include <boost/filesystem.hpp>

namespace esys::repo::grepo::test
{

/*! \class find_path_by_repo01GRepo esys/repo/grepo/test/find_path_by_repo01_grepo.cpp
 * "esys/repo/grepo/test/find_path_by_repo01_grepo.cpp"
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(find_path_by_repo01GRepo)
{
    boost::filesystem::path file_path;

    file_path = repo::test::TestCaseCtrl::get().GetTestFilesFolder();
    file_path /= grepo::Manifest::get_folder_name();
    file_path /= "default02.xml";

    Manifest manifest;

    int result = manifest.read(file_path.string());
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    auto data = manifest.get_data();
    ESYSTEST_REQUIRE_EQUAL(data->get_locations().size(), 3);

    std::string path = data->find_repo_path_by_url("ssh://git@gitlab.com/libesys/esysos");
    ESYSTEST_REQUIRE_EQUAL(path, "src/esysos");

    path = data->find_repo_path_by_url("ssh://git@gitlab.com/libesys/esysos.git");
    ESYSTEST_REQUIRE_EQUAL(path, "src/esysos");

    path = data->find_repo_path_by_url("https://gitlab.com/libesys/esysos");
    ESYSTEST_REQUIRE_EQUAL(path, "src/esysos");

    path = data->find_repo_path_by_url("ssh://git@gitlab.com/libesys/extlib/arduino1710");
    ESYSTEST_REQUIRE_EQUAL(path, "extlib/arduino1710");

    path = data->find_repo_path_by_url("https://gitlab.com/libesys/extlib/arduino1710");
    ESYSTEST_REQUIRE_EQUAL(path, "extlib/arduino1710");
}

} // namespace esys::repo::grepo::test
