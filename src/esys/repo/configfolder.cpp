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

#include <boost/filesystem.hpp>

namespace esys
{

namespace repo
{

ConfigFolder::ConfigFolder()
{
}

ConfigFolder::~ConfigFolder()
{
}

void ConfigFolder::set_parent_path(const std::string &parent_path)
{
    boost::filesystem::path path = parent_path;

    boost::filesystem::absolute(path).make_preferred();

    m_parent_path = boost::filesystem::absolute(path).make_preferred().string();
}

const std::string &ConfigFolder::get_parent_path() const
{
    return m_parent_path;
}

void ConfigFolder::populate_all_pathes()
{
    boost::filesystem::path path = get_parent_path();
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
    if (!parent_path.empty()) set_parent_path(parent_path);

    if (!boost::filesystem::exists(get_parent_path()))
    {
        return -1;
    }

    populate_all_pathes();

    if (boost::filesystem::exists(get_path()))
    {
        return -1;
    }

    bool result = boost::filesystem::create_directory(get_path());
    if (!result) return -1;

    result = boost::filesystem::create_directory(get_temp_path());
    if (!result) return -1;

    return 0;
}

int ConfigFolder::open(const std::string &parent_path)
{
    if (!parent_path.empty()) set_parent_path(parent_path);

    populate_all_pathes();

    if (!boost::filesystem::exists(get_path()))
    {
        return -1;
    }

    m_config_file = std::make_shared<ConfigFile>();
    int result = m_config_file->open(get_config_file_path());
    if (result < 0) return result;
    set_config(m_config_file->get_config());

    return 0;
}

int ConfigFolder::write(const std::string &parent_path)
{
    if (!parent_path.empty()) set_parent_path(parent_path);

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

std::shared_ptr<Config> ConfigFolder::get_config()
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
    return m_config_file->write(get_config_file_path());
}

} // namespace repo

} // namespace esys