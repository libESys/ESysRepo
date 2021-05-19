/*!
 * \file esys/repo/test/configfilewrite01.cpp
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

#include <esys/repo/configfile.h>

#include <boost/filesystem.hpp>

#include <iostream>

namespace esys
{

namespace repo
{

namespace test
{

/*! \class ConfigFileWrite01 esys/repo/test/configfilewrite01.cpp
 * "esys/repo/test/configfilewrite01.cpp"
 *
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(ConfigFileWrite01)
{
    boost::filesystem::path path;

    path = repo::test::TestCaseCtrl::get().GetTempFilesFolder();
    path /= ("configfilewrite01");

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

    ConfigFile config_file;
    std::shared_ptr<Config> cfg = std::make_shared<Config>();

    cfg->set_manifest_type(manifest::Type::GOOGLE_MANIFEST);
    cfg->set_manifest_path("grepo/default.xml");

    path /= "config.json";
    config_file.set_config(cfg);

    int result = config_file.write(path.string());
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    ConfigFile config_file_rd;

    result = config_file_rd.open(path.string());
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    auto cfg_rd = config_file_rd.get_config();
    ESYSTEST_REQUIRE_NE(cfg_rd, nullptr);

    bool equal = (*cfg_rd == *cfg);
    ESYSTEST_REQUIRE_EQUAL(equal, true);
}

} // namespace test

} // namespace repo

} // namespace esys
