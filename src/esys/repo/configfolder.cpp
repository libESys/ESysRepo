/*!
 * \file esys/repo/configfolder.cpp
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
#include "esys/repo/configfolder.h"
#include "esys/repo/manifest/base.h"
#include "esys/repo/grepo/manifest.h"

#include <boost/filesystem.hpp>

namespace esys
{

namespace repo
{

ConfigFolder::ConfigFolder()
    : log::User()
{
}

ConfigFolder::~ConfigFolder()
{
}

void ConfigFolder::set_workspace_path(const std::string &parent_path)
{
    boost::filesystem::path path = parent_path;

    boost::filesystem::absolute(path).make_preferred();

    m_parent_path = boost::filesystem::absolute(path).make_preferred().string();
}

const std::string &ConfigFolder::get_workspace_path() const
{
    return m_parent_path;
}

void ConfigFolder::populate_all_pathes()
{
    boost::filesystem::path path = get_workspace_path();
    boost::filesystem::path temp;
    boost::filesystem::path config_file;

    path /= ".esysrepo";
    m_path = path.string();

    temp = path;
    temp /= "temp";
    m_temp_path = temp.string();

    config_file = path;
    config_file /= "config.json";
    m_config_file_path = config_file.string();
}

int ConfigFolder::create(const std::string &parent_path)
{
    if (!parent_path.empty()) set_workspace_path(parent_path);

    if (!boost::filesystem::exists(get_workspace_path()))
    {
        boost::filesystem::path rel_parent_path = boost::filesystem::relative(get_workspace_path());

        bool result = boost::filesystem::create_directories(get_workspace_path());
        if (result)
        {
            info("Created folder : " + rel_parent_path.string());
        }
        else
        {
            error("Couldn't create output folder : " + rel_parent_path.string());
            return -1;
        }
    }

    populate_all_pathes();

    boost::filesystem::path rel_path = boost::filesystem::relative(get_path());

    if (boost::filesystem::exists(get_path()))
    {
        error("The following folder already exits : " + rel_path.string());
        return -1;
    }

    bool result = boost::filesystem::create_directory(get_path());
    if (!result)
    {
        error("The following folder couldn't be created : " + rel_path.string());
        return -1;
    }
    else
        info("Created folder : " + rel_path.string());

    boost::filesystem::path rel_temp_path = boost::filesystem::relative(get_temp_path());
    result = boost::filesystem::create_directory(get_temp_path());
    if (!result)
    {
        error("The following folder couldn't be created : " + rel_temp_path.string());
        return -1;
    }
    else
        info("Created folder : " + rel_temp_path.string());
    return 0;
}

int ConfigFolder::open(const std::string &parent_path)
{
    if (!parent_path.empty()) set_workspace_path(parent_path);

    populate_all_pathes();

    boost::filesystem::path rel_path = boost::filesystem::relative(get_path());
    if (!boost::filesystem::exists(get_path()))
    {
        error("The following folder is not existing : " + rel_path.string());
        return -1;
    }

    boost::filesystem::path rel_config_file_path = boost::filesystem::relative(get_config_file_path());
    if (!boost::filesystem::exists(get_config_file_path()))
    {
        error("The esysrepo config file can't be found : " + rel_config_file_path.string());
        return -1;
    }

    m_config_file = std::make_shared<ConfigFile>();
    int result = m_config_file->open(get_config_file_path());
    if (result < 0)
    {
        error("The esysrepo config file couldn't opened : " + rel_config_file_path.string());
        return result;
    }
    set_config(m_config_file->get_config());

    return 0;
}

int ConfigFolder::write(const std::string &parent_path)
{
    if (!parent_path.empty()) set_workspace_path(parent_path);

    return -1;
}

const std::string &ConfigFolder::get_path() const
{
    return m_path;
}

const std::string &ConfigFolder::get_temp_path() const
{
    return m_temp_path;
}

const std::string &ConfigFolder::get_config_file_path() const
{
    return m_config_file_path;
}

std::string ConfigFolder::get_manifest_repo_path() const
{
    boost::filesystem::path repo_path = get_path();
    if (get_config() == nullptr) return "";

    repo_path /= get_config()->get_manifest_path();
    repo_path = repo_path.parent_path().normalize().make_preferred();

    return repo_path.string();
}

std::string ConfigFolder::get_manifest_rel_file_name() const
{
    assert(get_config() != nullptr);

    std::string folder_name;

    switch (get_config()->get_manifest_type())
    {
        case manifest::Type::ESYSREPO_MANIFEST: folder_name = manifest::Base::get_folder_name(); break;
        case manifest::Type::GOOGLE_MANIFEST: folder_name = grepo::Manifest::get_folder_name(); break;
    }

    boost::filesystem::path manifest_path = get_config()->get_manifest_path();

    auto rel_folder_path = boost::filesystem::relative(manifest_path, folder_name);
    return rel_folder_path.string();
}

std::shared_ptr<Config> ConfigFolder::get_config()
{
    return m_config;
}

std::shared_ptr<Config> ConfigFolder::get_config() const
{
    return m_config;
}

void ConfigFolder::set_config(std::shared_ptr<Config> config)
{
    m_config = config;
}

std::shared_ptr<Config> ConfigFolder::get_or_new_config()
{
    auto cfg = get_config();

    if (cfg != nullptr) return cfg;

    set_config(std::make_shared<Config>());

    return get_config();
}

int ConfigFolder::write_config_file()
{
    m_config_file = std::make_shared<ConfigFile>();
    m_config_file->set_config(get_config());
    int result = m_config_file->write(get_config_file_path());
    boost::filesystem::path rel_config_file_path = boost::filesystem::relative(get_config_file_path());
    if (result < 0)
        error("Couldn't write the esysrepo config file : " + rel_config_file_path.string());
    else
        debug(0, "Wrote the esysrepo config file : " + rel_config_file_path.string());
    return result;
}

bool ConfigFolder::is_config_folder(const std::string &path)
{
    boost::filesystem::path folder = path;
    folder /= ".esysrepo";
    return boost::filesystem::exists(folder);
}

} // namespace repo

} // namespace esys
