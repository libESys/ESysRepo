/*!
 * \file esys/repo/manifest/repository_manifest.cpp
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
#include "esys/repo/manifest/repository.h"
#include "esys/repo/manifest/group.h"

#include <boost/filesystem.hpp>

namespace esys
{

namespace repo
{

namespace manifest
{

Repository::Repository()
{
}

Repository::Repository(const std::string &name, const std::string &path)
    : m_name(name)
    , m_path(path)
{
}

Repository::~Repository()
{
}

void Repository::set_name(const std::string &name)
{
    m_name = name;
}

const std::string &Repository::get_name() const
{
    return m_name;
}

void Repository::set_path(const std::string &path)
{
    boost::filesystem::path gen_path = path;

    m_path = gen_path.generic().string();
}

const std::string &Repository::get_path() const
{
    return m_path;
}

void Repository::set_revision(const std::string &revision)
{
    m_revision = revision;
}

const std::string Repository::get_revision() const
{
    return m_revision;
}

void Repository::set_location(const std::string &location_str)
{
    m_location_str = location_str;
}

const std::string &Repository::get_location_str() const
{
    return m_location_str;
}

void Repository::set_location(Location *location)
{
    m_location = location;
}

Location *Repository::get_location() const
{
    return m_location;
}

std::vector<Group *> &Repository::get_groups()
{
    return m_groups;
}

const std::vector<Group *> &Repository::get_groups() const
{
    return m_groups;
}

bool Repository::operator==(const Repository &repository) const
{
    if (get_name() != repository.get_name()) return false;
    if (get_path() != repository.get_path()) return false;
    if (get_revision() != repository.get_revision()) return false;
    if (get_location_str() != repository.get_location_str()) return false;

    if (get_groups().size() != repository.get_groups().size()) return false;

    for (std::size_t idx = 0; idx < get_groups().size(); ++idx)
    {
        if (get_groups()[idx]->get_name() != repository.get_groups()[idx]->get_name()) return false;
    }

    return true;
}

bool Repository::operator!=(const Repository &repository) const
{
    return !operator==(repository);
}

} // namespace manifest

} // namespace repo

} // namespace esys
