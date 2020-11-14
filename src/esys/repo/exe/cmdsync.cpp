/*!
 * \file esys/repo/exe/cmdsync.cpp
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
#include "esys/repo/exe/cmdsync.h"
#include "esys/repo/manifest/clonerepos.h"

namespace esys
{

namespace repo
{

namespace exe
{

CmdSync::CmdSync()
{
}

CmdSync::~CmdSync()
{
}

void CmdSync::set_parent_path(const std::string &parent_path)
{
    m_parent_path = parent_path;
}

const std::string &CmdSync::get_parent_path() const
{
    return m_parent_path;
}

void CmdSync::set_manifest(std::shared_ptr<Manifest> manifest)
{
    m_manifest = manifest;
}

std::shared_ptr<Manifest> CmdSync::get_manifest()
{
    return m_manifest;
}

const std::shared_ptr<Manifest> CmdSync::get_manifest() const
{
    return m_manifest;
}

void CmdSync::set_config_folder(std::shared_ptr<ConfigFolder> config_folder)
{
    m_config_folder = config_folder;
}

std::shared_ptr<ConfigFolder> CmdSync::get_config_folder()
{
    return m_config_folder;
}

const std::shared_ptr<ConfigFolder> CmdSync::get_config_folder() const
{
    return m_config_folder;
}

void CmdSync::set_fetcher(std::shared_ptr<manifest::Fetch> fetcher)
{
    m_fetcher = fetcher;
}

std::shared_ptr<manifest::Fetch> CmdSync::get_fetcher()
{
    return m_fetcher;
}

const std::shared_ptr<manifest::Fetch> CmdSync::get_fetcher() const
{
    return m_fetcher;
}

void CmdSync::set_git(std::shared_ptr<GitBase> git)
{
    m_git = git;
}

std::shared_ptr<GitBase> CmdSync::get_git()
{
    return m_git;
}

const std::shared_ptr<GitBase> CmdSync::get_git() const
{
    return m_git;
}

int CmdSync::run()
{
    int result;

    result = open_esysrepo_folder();
    if (result < 0) return result;

    if (get_fetcher() == nullptr) set_fetcher(std::make_shared<manifest::Fetch>());
    if (get_manifest() == nullptr) set_manifest(std::make_shared<Manifest>());

    get_fetcher()->set_manifest(get_manifest());
    get_fetcher()->set_config_folder(get_config_folder());

    result = get_fetcher()->run();
    if (result < 0) return result;

    manifest::CloneRepos clone_repos;

    clone_repos.set_config_folder(get_config_folder());
    clone_repos.set_git(get_git());
    clone_repos.set_manifest(get_manifest());

    return clone_repos.run();
}

int CmdSync::open_esysrepo_folder()
{
    auto config_folder = std::make_shared<ConfigFolder>();

    set_config_folder(config_folder);

    return config_folder->open(get_parent_path());
}

} // namespace exe

} // namespace repo

} // namespace esys