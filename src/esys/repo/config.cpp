/*!
 * \file esys/repo/config.cpp
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
#include "esys/repo/config.h"

namespace esys
{

namespace repo
{

Config::Config() = default;

Config::~Config() = default;

void Config::set_manifest_type(manifest::Type manifest_type)
{
    m_manifest_type = manifest_type;
}

manifest::Type Config::get_manifest_type() const
{
    return m_manifest_type;
}

void Config::set_manifest_path(const std::string &manifest_path)
{
    m_manifest_path = manifest_path;
}

const std::string &Config::get_manifest_path() const
{
    return m_manifest_path;
}

bool Config::operator==(const Config &cfg) const
{
    if (get_manifest_type() != cfg.get_manifest_type()) return false;
    if (get_manifest_path() != cfg.get_manifest_path()) return false;

    return true;
}

bool Config::operator!=(const Config &cfg) const
{
    return !operator==(cfg);
}


void Config::operator=(const Config &cfg)
{
    set_manifest_type(cfg.get_manifest_type());
    set_manifest_path(cfg.get_manifest_path());
}

} // namespace repo

} // namespace esys
