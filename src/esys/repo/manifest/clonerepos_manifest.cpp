/*!
 * \file esys/repo/manifest/clonerepos_mannifest.cpp
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
#include "esys/repo/manifest/clonerepos.h"
#include "esys/repo/manifest/location.h"

#include <boost/filesystem.hpp>

namespace esys
{

namespace repo
{

namespace manifest
{

CloneRepos::CloneRepos()
{
}

CloneRepos::~CloneRepos()
{
}

void CloneRepos::set_manifest(std::shared_ptr<Manifest> manifest)
{
    m_manifest = manifest;
}

std::shared_ptr<Manifest> CloneRepos::get_manifest()
{
    return m_manifest;
}

const std::shared_ptr<Manifest> CloneRepos::get_manifest() const
{
    return m_manifest;
}

void CloneRepos::set_config_folder(std::shared_ptr<ConfigFolder> config_folder)
{
    m_config_folder = config_folder;
}

std::shared_ptr<ConfigFolder> CloneRepos::get_config_folder()
{
    return m_config_folder;
}

const std::shared_ptr<ConfigFolder> CloneRepos::get_config_folder() const
{
    return m_config_folder;
}

void CloneRepos::set_git(std::shared_ptr<GitBase> git)
{
    m_git = git;
}

std::shared_ptr<GitBase> CloneRepos::get_git()
{
    return m_git;
}

const std::shared_ptr<GitBase> CloneRepos::get_git() const
{
    return m_git;
}

int CloneRepos::run()
{
    if (get_manifest() == nullptr) return -1;
    if (get_config_folder() == nullptr) return -1;
    if (get_git() == nullptr) return -1;

    int local_result;
    int result = 0;

    for (auto location : get_manifest()->get_locations())
    {
        for (auto repo : location->get_repos())
        {
            local_result = clone(repo);
            if (local_result < 0)
            {
                --result;
                //! \TODO
            }
        }
    }
    return result;
}

int CloneRepos::clone(std::shared_ptr<manifest::Repository> repository)
{
    std::string url = repository->get_location()->get_address();
    url += "/" + repository->get_name();

    boost::filesystem::path path = get_config_folder()->get_parent_path();
    if (repository->get_path() != ".") path /= repository->get_path();

    int result = get_git()->clone(url, path.string());
    if (result < 0) return result;

    result = get_git()->close();

    return result;
}

} // namespace manifest

} // namespace repo

} // namespace esys
