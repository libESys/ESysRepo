/*!
 * \file esys/repo/manifest/loadergrepo_manifest.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/manifest/loadergrepo.h"
#include "esys/repo/grepo/manifest.h"

#include <boost/filesystem.hpp>

namespace esys::repo::manifest
{

LoaderGRepo::LoaderGRepo()
    : LoaderBase()
{
}

LoaderGRepo::~LoaderGRepo() = default;

Result LoaderGRepo::run()
{
    std::shared_ptr<Config> config;
    boost::filesystem::path path;

    if (get_config_folder() != nullptr)
    {
        config = get_config_folder()->get_config();
        if (config == nullptr) return ESYSREPO_RESULT(ResultCode::INTERNAL_ERROR);

        path = get_config_folder()->get_path();
        path /= get_config_folder()->get_config()->get_manifest_path();
    }
    else if (get_config() != nullptr)
    {
        config = get_config();
        path = config->get_manifest_path();
    }
    else
        return ESYSREPO_RESULT(ResultCode::INTERNAL_ERROR);

    path = boost::filesystem::absolute(path).make_preferred();
    if (path.empty()) return ESYSREPO_RESULT(ResultCode::EMPTY_PATH);

    if ((config->get_manifest_type() != manifest::Type::GOOGLE_MANIFEST)
        && (config->get_manifest_type() != manifest::Type::RAW_GOOGLE_MANIFEST))
        return ESYSREPO_RESULT(ResultCode::INTERNAL_ERROR);

    grepo::Manifest loader;

    if (get_manifest() == nullptr) set_manifest(std::make_shared<Manifest>());

    loader.set_data(get_manifest());

    boost::filesystem::path rel_path = boost::filesystem::relative(path);

    Result result = loader.read(path.string());
    if (result.error())
        error("Couldn't load Google repo manifest : " + rel_path.string());
    else
        debug(0, "Loaded Google repo manifest : " + rel_path.string());

    return ESYSREPO_RESULT(result);
}

} // namespace esys::repo::manifest
