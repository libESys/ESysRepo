/*!
 * \file esys/repo/manifest.cpp
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
#include "esys/repo/manifest.h"

#include <cassert>

namespace esys
{

namespace repo
{

Manifest::Manifest()
{
}

Manifest::~Manifest()
{
}

void Manifest::set_type(manifest::Type type)
{
    m_type = type;
}

manifest::Type Manifest::get_type() const
{
    return m_type;
}

int Manifest::add_location(std::shared_ptr<manifest::Location> location, bool is_default)
{
    assert(location != nullptr);
    assert(!location->get_name().empty());

    auto it = m_map_locations.find(location->get_name());
    if (it != m_map_locations.end()) return -1;

    m_locations.push_back(location);
    m_map_locations[location->get_name()] = location;
    if (is_default) set_default_location(location);

    return 0;
}

std::vector<std::shared_ptr<manifest::Location>> &Manifest::get_locations()
{
    return m_locations;
}

const std::vector<std::shared_ptr<manifest::Location>> &Manifest::get_locations() const
{
    return m_locations;
}

std::map<std::string, std::shared_ptr<manifest::Location>> &Manifest::get_map_locations()
{
    return m_map_locations;
}

const std::map<std::string, std::shared_ptr<manifest::Location>> &Manifest::get_map_locations() const
{
    return m_map_locations;
}

std::shared_ptr<manifest::Location> Manifest::find_location(const std::string &name)
{
    auto it = m_map_locations.find(name);

    if (it == m_map_locations.end()) return nullptr;

    return it->second;
}

void Manifest::set_default_location(std::shared_ptr<manifest::Location> default_location)
{
    m_default_location = default_location;
}

std::shared_ptr<manifest::Location> Manifest::get_default_location()
{
    if (m_default_location != nullptr) return m_default_location;

    if (m_default_location_str.empty()) return nullptr;

    return find_location(m_default_location_str);
}

const std::shared_ptr<manifest::Location> Manifest::get_default_location() const
{
    return m_default_location;
}

void Manifest::set_default_location(const std::string &default_location_str)
{
    m_default_location_str = default_location_str;
}

const std::string &Manifest::get_default_location_str() const
{
    return m_default_location_str;
}

void Manifest::set_default_revision(const std::string &default_revision)
{
    m_default_revision = default_revision;
}

const std::string Manifest::get_default_revision() const
{
    return m_default_revision;
}

void Manifest::set_default_job_count(int default_job_count)
{
    m_default_job_count = default_job_count;
}

int Manifest::get_default_job_count() const
{
    return m_default_job_count;
}

} // namespace repo

} // namespace esys