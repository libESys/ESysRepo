/*!
 * \file esys/repo/configfile.cpp
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
#include "esys/repo/configfile.h"
#include "esys/repo/configfileimpl.h"

namespace esys::repo
{

ConfigFile::ConfigFile()
{
    m_impl = std::make_unique<ConfigFileImpl>(this);
}

ConfigFile::~ConfigFile() = default;

void ConfigFile::set_path(const std::string &path)
{
    m_path = path;
}

const std::string &ConfigFile::get_path() const
{
    return m_path;
}

void ConfigFile::set_config(std::shared_ptr<Config> config)
{
    m_config = config;
}

std::shared_ptr<Config> ConfigFile::get_config() const
{
    return m_config;
}

int ConfigFile::open(const std::string &path)
{
    return get_impl()->open(path);
}

int ConfigFile::write(const std::string &path)
{
    return get_impl()->write(path);
}

ConfigFileImpl *ConfigFile::get_impl()
{
    return m_impl.get();
}

const ConfigFileImpl *ConfigFile::get_impl() const
{
    return m_impl.get();
}

} // namespace esys::repo
