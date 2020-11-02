/*!
 * \file esys/repo/manifest/location_manifest.cpp
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
#include "esys/repo/manifest/location.h"
#include "esys/repo/manifest/repository.h"

namespace esys
{

namespace repo
{

namespace manifest
{

Location::Location()
    : std::enable_shared_from_this<Location>()
{
}

Location::Location(const std::string &name, const std::string &address)
    : std::enable_shared_from_this<Location>()
    , m_name(name)
    , m_address(address)
{
}

Location::~Location()
{
}

void Location::set_name(const std::string &name)
{
    m_name = name;
}

const std::string &Location::get_name() const
{
    return m_name;
}

void Location::set_address(const std::string &address)
{
    m_address = address;
}

const std::string &Location::get_address() const
{
    return m_address;
}

std::shared_ptr<Repository> Location::add_repo(const std::string &name, const std::string &path)
{
    auto repo = std::make_shared<Repository>(name, path);

    repo->set_location(this);

    get_repos().push_back(repo);

    return repo;
}

void Location::add_repo(std::shared_ptr<Repository> repo)
{
    repo->set_location(this);

    get_repos().push_back(repo);
}

std::vector<std::shared_ptr<Repository>> &Location::get_repos()
{
    return m_repos;
}

const std::vector<std::shared_ptr<Repository>> &Location::get_repos() const
{
    return m_repos;
}

} // namespace manifest

} // namespace repo

} // namespace esys