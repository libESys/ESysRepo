/*!
 * \file esys/repo/manifest/group_manifest.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2021 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/manifest/group.h"
#include "esys/repo/manifest/repository.h"

#include <boost/filesystem.hpp>

namespace esys
{

namespace repo
{

namespace manifest
{

Group::Group()
    : std::enable_shared_from_this<Group>()
{
}

Group::Group(const std::string &name)
    : std::enable_shared_from_this<Group>()
    , m_name(name)
{
}

Group::~Group()
{
}

void Group::set_name(const std::string &name)
{
    m_name = name;
}

const std::string &Group::get_name() const
{
    return m_name;
}

void Group::add_repo(std::shared_ptr<Repository> repo)
{
    get_repos().push_back(repo);
    m_map_repos_by_name[repo->get_name()] = repo;
    m_map_repos_by_path[repo->get_path()] = repo;
}

std::vector<std::shared_ptr<Repository>> &Group::get_repos()
{
    return m_repos;
}

const std::vector<std::shared_ptr<Repository>> &Group::get_repos() const
{
    return m_repos;
}

std::shared_ptr<Repository> Group::find_repo_by_path(const std::string &path)
{
    boost::filesystem::path gen_path = path;

    auto it = m_map_repos_by_path.find(gen_path.generic().string());

    if (it == m_map_repos_by_path.end()) return nullptr;
    return it->second;
}

std::shared_ptr<Repository> Group::find_repo_by_name(const std::string &name)
{
    auto it = m_map_repos_by_name.find(name);

    if (it == m_map_repos_by_name.end()) return nullptr;
    return it->second;
}

} // namespace manifest

} // namespace repo

} // namespace esys
