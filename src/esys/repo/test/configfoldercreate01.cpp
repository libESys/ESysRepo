/*!
 * \file esys/repo/test/configfoldercreate01.cpp
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

#include <esys/repo/configfolder.h>

#include <boost/filesystem.hpp>

#include <iostream>

namespace esys
{

namespace repo
{

namespace test
{

/*! \class ConfigFolderCreate01 esys/repo/test/configfoldercreate01.cpp
 * "esys/repo/test/configfoldercreate01.cpp"
 *
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(ConfigFolderCreate01)
{
    boost::filesystem::path parent_path;

    parent_path = repo::test::TestCaseCtrl::get().GetTempFilesFolder();
    parent_path /= ("configfoldercreate01");

    bool remove_all = true;

    try
    {
        if (boost::filesystem::exists(parent_path)) boost::filesystem::remove_all(parent_path);
    }
    catch (const boost::filesystem::filesystem_error &e)
    {
        remove_all = false;
        std::cerr << e.what() << std::endl;
    }

    ESYSTEST_REQUIRE_EQUAL(remove_all, true);

    bool folder_created = boost::filesystem::create_directories(parent_path);
    ESYSTEST_REQUIRE_EQUAL(folder_created, true);

    ConfigFolder config_folder;
    std::shared_ptr<Config> cfg = std::make_shared<Config>();

    cfg->set_manifest_type(manifest::Type::GOOGLE_MANIFEST);
    cfg->set_manifest_path("grepo/default.xml");

    config_folder.set_config(cfg);
    config_folder.set_workspace_path(parent_path.string());

    Result result = config_folder.create();
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);
}

} // namespace test

} // namespace repo

} // namespace esys
