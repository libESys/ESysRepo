/*!
 * \file esys/repo/manifest/loaderesysrepo_manifest.cpp
 * \brief
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/manifest/loaderesysrepo.h"
#include "esys/repo/manifest/file.h"

#include <boost/filesystem.hpp>

namespace esys::repo::manifest
{

LoaderESysRepo::LoaderESysRepo()
    : LoaderBase()
{
}

LoaderESysRepo::~LoaderESysRepo() = default;

int LoaderESysRepo::run()
{
    if (get_config_folder() == nullptr) return -1;
    if (get_config_folder()->get_config() == nullptr) return -1;
    if (get_config_folder()->get_config()->get_manifest_type() != manifest::Type::ESYSREPO_MANIFEST) return -1;
    if (get_config_folder()->get_config()->get_manifest_path().empty()) return -1;

    boost::filesystem::path path;
    manifest::File loader;

    path = get_config_folder()->get_path();
    path /= get_config_folder()->get_config()->get_manifest_path();
    path = boost::filesystem::absolute(path).make_preferred();

    if (get_manifest() == nullptr) set_manifest(std::make_shared<Manifest>());

    loader.set_data(get_manifest());

    boost::filesystem::path rel_path = boost::filesystem::relative(path);

    int result = loader.read(path.string());
    if (result < 0)
        error("Couldn't load ESysRepo manifest : " + rel_path.string());
    else
        debug(0, "Loaded ESysRepo manifest : " + rel_path.string());

    return result;
}

} // namespace esys::repo::manifest
