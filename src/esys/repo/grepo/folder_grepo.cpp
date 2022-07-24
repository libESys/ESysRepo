/*!
 * \file esys/repo/grepo/folder_grepo.cpp
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
#include "esys/repo/grepo/folder.h"
#include "esys/repo/grepo/manifest.h"

#include <boost/filesystem.hpp>

namespace esys::repo::grepo
{

Folder::Folder(const std::string &folder_path)
    : m_folder_path(folder_path)
{
}

Folder::~Folder() = default;

Result Folder::open(const std::string &folder_path)
{
    if (!folder_path.empty()) set_folder_path(folder_path);

    if (get_folder_path().empty()) return ESYSREPO_RESULT(ResultCode::EMPTY_PATH);

    boost::filesystem::path path = get_folder_path();
    if (!boost::filesystem::exists(path)) return ESYSREPO_RESULT(ResultCode::PATH_NOT_EXISTING, path.string());

    if (path.filename() != ".repo") path /= ".repo";

    boost::filesystem::path manifest_xml = path / "manifest.xml";
    if (!boost::filesystem::exists(manifest_xml)) return ESYSREPO_RESULT(ResultCode::FILE_NOT_EXISTING, path.string());

    auto manifest = std::make_shared<Manifest>();

    Result result = manifest->read(manifest_xml.string());
    if (result.error()) return ESYSREPO_RESULT(result);

    auto data = manifest->get_data();
    if (data->get_includes().size() != 1) ESYSREPO_RESULT(ResultCode::GREPO_FOLDER_NO_INCLUDE, path.string());

    auto include = data->get_includes()[0];
    if (include == nullptr) return ESYSREPO_RESULT(ResultCode::INTERNAL_ERROR);

    auto config = get_or_new_config();
    config->set_manifest_type(manifest::Type::RAW_GOOGLE_MANIFEST);
    config->set_manifest_kind(manifest::Kind::ISOLATED);
    config->set_manifest_format(manifest::Format::XML);
    config->set_manifest_path(include->get_name());
    set_config(config);
    return ESYSREPO_RESULT(ResultCode::OK);
}

void Folder::set_folder_path(const std::string &folder_path)
{
    m_folder_path = folder_path;
}

const std::string &Folder::get_folder_path() const
{
    return m_folder_path;
}

std::shared_ptr<Config> Folder::get_config() const
{
    return m_config;
}

void Folder::set_config(std::shared_ptr<Config> config)
{
    m_config = config;
}

std::shared_ptr<Config> Folder::get_or_new_config()
{
    auto cfg = get_config();

    if (cfg != nullptr) return cfg;

    set_config(std::make_shared<Config>());

    return get_config();
}

} // namespace esys::repo::grepo
