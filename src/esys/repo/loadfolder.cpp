/*!
 * \file esys/repo/loadfolder.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/loadfolder.h"
#include "esys/repo/manifest/detect.h"
#include "esys/repo/manifest/loader.h"

namespace esys::repo
{

LoadFolder::LoadFolder(const std::string &folder_path)
    : m_folder_path(folder_path)
{
}

LoadFolder::~LoadFolder() = default;

void LoadFolder::set_folder_path(const std::string &folder_path)
{
    m_folder_path = folder_path;
}

const std::string &LoadFolder::get_folder_path() const
{
    return m_folder_path;
}

Result LoadFolder::run(const std::string &folder_path)
{
    if (!folder_path.empty()) set_folder_path(folder_path);

    auto detect = std::make_unique<manifest::Detect>();

    detect->set_folder_path(folder_path);
    Result result = detect->detect();
    if (result.error()) return ESYSREPO_RESULT(result);

    auto loader = std::make_unique<manifest::Loader>();
    if (detect->get_config_folder() != nullptr)
    {
        loader->set_config_folder(detect->get_config_folder());
    }
    else if (detect->get_config() != nullptr)
    {
        loader->set_config(detect->get_config());
    }
    else
        return ESYSREPO_RESULT(ResultCode::INTERNAL_ERROR);

    result = loader->run();
    if (result.error()) return ESYSREPO_RESULT(result);
    set_manifest(loader->get_manifest());
    return ESYSREPO_RESULT(ResultCode::OK);
}

std::string LoadFolder::find_repo_path_by_url(const std::string &url)
{
    if (get_manifest() == nullptr) return "";

    return get_manifest()->find_repo_path_by_url(url);
}

std::shared_ptr<manifest::Repository> LoadFolder::find_repo_by_url(const std::string &url)
{
    if (get_manifest() == nullptr) return nullptr;

    return get_manifest()->find_repo_by_url(url);
}

std::shared_ptr<Manifest> LoadFolder::get_manifest()
{
    return m_manifest;
}

void LoadFolder::set_manifest(std::shared_ptr<Manifest> manifest)
{
    m_manifest = manifest;
}

} // namespace esys::repo
