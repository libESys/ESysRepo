/*!
 * \file esys/repo/manifest/test/detect01_manifest.cpp
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
#include <esys/repo/manifest/detect.h>

namespace esys::repo::manifest::test
{

/*! \class Detect01 esys/repo/manifest/test/detect01_manifest.cpp
 * "esys/repo/manifest/test/detect01_manifest.cpp"
 *
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(Detect01)
{
    boost::filesystem::path folder_path;

    folder_path = repo::test::TestCaseCtrl::get().GetTestFilesFolder();
    folder_path /= grepo::Manifest::get_folder_name();
    folder_path /= "repo01";

    Detect detect;

    detect.set_folder_path(folder_path.string());
    int result = detect.detect();
    ESYSTEST_REQUIRE_EQUAL(result, 0);
}

} // namespace esys::repo::manifest::test
