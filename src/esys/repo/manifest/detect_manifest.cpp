/*!
 * \file esys/repo/manifest/detect_manifest.cpp
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
#include "esys/repo/manifest/detect.h"
#include "esys/repo/grepo/folder.h"

#include <boost/filesystem.hpp>

namespace esys::repo::manifest
{

Detect::Detect(const std::string &folder_path)
    : m_folder_path(folder_path)
{
}

Detect::~Detect() = default;

void Detect::set_folder_path(const std::string &folder_path)
{
    m_folder_path = folder_path;
}

const std::string &Detect::get_folder_path() const
{
    return m_folder_path;
}

int Detect::detect(std::shared_ptr<Config> config)
{
    if (get_folder_path().empty()) return -1;

    if (config != nullptr) set_config(config);
    config = get_config_or_new();

    boost::filesystem::path file_path = get_folder_path();
    file_path /= ".esysrepo";

    if (boost::filesystem::exists(file_path))
    {
        std::shared_ptr<ConfigFolder> config_folder = std::make_shared<ConfigFolder>();

        config_folder->set_config(config);
        int result = config_folder->open(get_folder_path());
        if (result == 0) set_config_folder(config_folder);
        return result;
    }

    file_path = get_folder_path();
    file_path /= ".repo";

    if (boost::filesystem::exists(file_path))
    {
        std::shared_ptr<grepo::Folder> folder = std::make_shared<grepo::Folder>();

        folder->set_config(config);
        int result = folder->open(get_folder_path());
        return result;
    }

    file_path = get_folder_path();
    file_path /= ".esysrepo.manifest";

    if (boost::filesystem::exists(file_path))
    {
        config->set_manifest_type(Type::ESYSREPO_MANIFEST);
        config->set_manifest_kind(Kind::EMBEDDED);
        config->set_manifest_path(file_path.string());
        config->set_manifest_format(Format::UNKNOWN);
        return 0;
    }

    file_path = get_folder_path();
    file_path /= ".esysrepo.manifest.xml";

    if (boost::filesystem::exists(file_path))
    {
        config->set_manifest_type(Type::ESYSREPO_MANIFEST);
        config->set_manifest_kind(Kind::EMBEDDED);
        config->set_manifest_path(file_path.string());
        config->set_manifest_format(Format::XML);
        return 0;
    }

    file_path = get_folder_path();
    file_path /= ".esysrepo.manifest.json";

    if (boost::filesystem::exists(file_path))
    {
        config->set_manifest_type(Type::ESYSREPO_MANIFEST);
        config->set_manifest_kind(Kind::EMBEDDED);
        config->set_manifest_path(file_path.string());
        config->set_manifest_format(Format::JSON);
        return 0;
    }

    return -1;
}

void Detect::set_config(std::shared_ptr<Config> config)
{
    m_config = config;
}

std::shared_ptr<Config> Detect::get_config()
{
    return m_config;
}

std::shared_ptr<Config> Detect::get_config_or_new()
{
    if (m_config == nullptr) m_config = std::make_shared<Config>();
    return m_config;
}

void Detect::set_config_folder(std::shared_ptr<ConfigFolder> config_folder)
{
    m_config_folder = config_folder;
}

std::shared_ptr<ConfigFolder> Detect::get_config_folder()
{
    return m_config_folder;
}

} // namespace esys::repo::manifest
