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

namespace esys::repo
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

void Config::set_manifest_kind(manifest::Kind manifest_kind)
{
    m_manifest_kind = manifest_kind;
}

manifest::Kind Config::get_manifest_kind() const
{
    return m_manifest_kind;
}

void Config::set_manifest_format(manifest::Format manifest_format)
{
    m_manifest_format = manifest_format;
}

manifest::Format Config::get_manifest_format() const
{
    return m_manifest_format;
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

Config &Config::operator=(const Config &cfg)
{
    if (cfg == *this) return *this;

    set_manifest_type(cfg.get_manifest_type());
    set_manifest_path(cfg.get_manifest_path());

    return *this;
}

bool Config::has_esysrepo_folder() const
{
    if ((get_manifest_type() == manifest::Type::GOOGLE_MANIFEST)
        || (get_manifest_type() == manifest::Type::ESYSREPO_MANIFEST))
        return true;
    return false;
}

} // namespace esys::repo
