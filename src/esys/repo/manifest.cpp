/*!
 * \file esys/repo/manifest.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2021 Michel Gillet
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
#include "esys/repo/manifest/repository.h"

#include <cassert>

namespace esys::repo
{

Manifest::Manifest() = default;

Manifest::~Manifest() = default;

void Manifest::set_type(manifest::Type type)
{
    m_type = type;
}

manifest::Type Manifest::get_type() const
{
    return m_type;
}

void Manifest::set_kind(manifest::Kind kind)
{
    m_kind = kind;
}

manifest::Kind Manifest::get_kind() const
{
    return m_kind;
}

void Manifest::set_format(manifest::Format format)
{
    m_format = format;
}

manifest::Format Manifest::get_format() const
{
    return m_format;
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

std::shared_ptr<manifest::Repository> Manifest::find_repo_by_path(const std::string &path)
{
    std::shared_ptr<manifest::Repository> repo;

    for (auto &location : get_locations())
    {
        repo = location->find_repo_by_path(path);
        if (repo != nullptr) return repo;
    }
    return nullptr;
}

std::string Manifest::find_repo_path_by_url(const std::string &git_repo_name)
{
    std::string path;

    for (auto &location : get_locations())
    {
        path = location->find_repo_path_by_url(git_repo_name);
        if (!path.empty()) return path;
    }
    return "";
}

std::shared_ptr<manifest::Repository> Manifest::find_repo_by_url(const std::string &url)
{
    std::shared_ptr<manifest::Repository> repo;

    for (auto &location : get_locations())
    {
        repo = location->find_repo_by_url(url);
        if (repo != nullptr) return repo;
    }
    return nullptr;

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

const std::string &Manifest::get_default_revision() const
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

std::string Manifest::get_repo_revision(std::shared_ptr<manifest::Repository> repo)
{
    if (!repo->get_revision().empty()) return repo->get_revision();
    return get_default_revision();
}

void Manifest::clear()
{
    m_type = manifest::Type::NOT_SET;
    m_locations.clear();
    m_map_locations.clear();
    m_map_locations_by_path.clear();
    m_default_location.reset();
    get_groups().clear();
    m_map_locations_by_path.clear();
    m_default_location_str.clear();
    m_default_revision = "master";
    m_default_job_count = 1;
}

manifest::Groups &Manifest::get_groups()
{
    return m_groups;
}

const manifest::Groups &Manifest::get_groups() const
{
    return m_groups;
}

void Manifest::add_include(std::shared_ptr<manifest::Include> include)
{
    m_includes.push_back(include);
}


std::vector<std::shared_ptr<manifest::Include>> &Manifest::get_includes()
{
    return m_includes;
}

const std::vector<std::shared_ptr<manifest::Include>> &Manifest::get_includes() const
{
    return m_includes;
}

bool Manifest::operator==(const Manifest &other) const
{
    if (get_type() != other.get_type()) return false;

    if (get_locations().size() != other.get_locations().size()) return false;

    for (std::size_t idx = 0; idx < get_locations().size(); ++idx)
    {
        if (*get_locations()[idx] != *other.get_locations()[idx]) return false;
    }

    if (get_includes().size() != other.get_includes().size()) return false;



    return true;
}

bool Manifest::operator!=(const Manifest &other) const
{
    return !operator==(other);
}

ESYSREPO_API std::ostream &operator<<(std::ostream &os, const Manifest &manifest)
{
    return os;
}

} // namespace esys::repo
