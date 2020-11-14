/*!
 * \file esys/repo/exe/cmdinit.cpp
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
#include "esys/repo/exe/cmdinit.h"
#include "esys/repo/filesystem.h"

#include <boost/filesystem.hpp>

#include <iostream>

namespace esys
{

namespace repo
{

namespace exe
{

CmdInit::CmdInit()
{
}

CmdInit::~CmdInit()
{
}

void CmdInit::set_url(const std::string &url)
{
    m_url = url;
}

const std::string &CmdInit::get_url() const
{
    return m_url;
}

void CmdInit::set_branch(const std::string &branch)
{
    m_branch = branch;
}

const std::string &CmdInit::get_branch() const
{
    return m_branch;
}

void CmdInit::set_manifest_name(const std::string &manifest_name)
{
    m_manifest_name = manifest_name;
}

const std::string &CmdInit::get_manifest_name() const
{
    return m_manifest_name;
}

void CmdInit::set_google_manifest(bool google_manifest)
{
    m_google_manifest = google_manifest;
    m_manifest_type = manifest::Type::GOOGLE_MANIFEST;
}

bool CmdInit::get_google_manifest() const
{
    return m_google_manifest;
}

void CmdInit::set_git_super_project(bool git_super_project)
{
    m_git_super_project = git_super_project;
    m_manifest_type = manifest::Type::GOOGLE_MANIFEST;
}

bool CmdInit::get_git_super_project() const
{
    return m_git_super_project;
}

void CmdInit::set_parent_path(const std::string &parent_path)
{
    m_parent_path = parent_path;
}

const std::string &CmdInit::get_parent_path() const
{
    return m_parent_path;
}

void CmdInit::set_force(bool force)
{
    m_force = force;
}

bool CmdInit::get_force() const
{
    return m_force;
}

void CmdInit::set_manifest(std::shared_ptr<Manifest> manifest)
{
    m_manifest = manifest;
}

std::shared_ptr<Manifest> CmdInit::get_manifest()
{
    return m_manifest;
}

const std::shared_ptr<Manifest> CmdInit::get_manifest() const
{
    return m_manifest;
}

void CmdInit::set_fetcher(std::shared_ptr<manifest::Fetch> fetcher)
{
    m_fetcher = fetcher;
}

std::shared_ptr<manifest::Fetch> CmdInit::get_fetcher()
{
    return m_fetcher;
}

const std::shared_ptr<manifest::Fetch> CmdInit::get_fetcher() const
{
    return m_fetcher;
}

void CmdInit::set_config_folder(std::shared_ptr<ConfigFolder> config_folder)
{
    m_config_folder = config_folder;
}

std::shared_ptr<ConfigFolder> CmdInit::get_config_folder()
{
    return m_config_folder;
}

const std::shared_ptr<ConfigFolder> CmdInit::get_config_folder() const
{
    return m_config_folder;
}

void CmdInit::set_git(std::shared_ptr<GitBase> git)
{
    m_git = git;
}

std::shared_ptr<GitBase> CmdInit::get_git()
{
    return m_git;
}

const std::shared_ptr<GitBase> CmdInit::get_git() const
{
    return m_git;
}

int CmdInit::run()
{
    int result;

    result = create_esysrepo_folder();
    if (result < 0) return result;

    result = fetch_manifest();
    if (result < 0) return result;

    return 0;
}

int CmdInit::fetch_manifest()
{
    if (get_google_manifest())
        return fetch_google_manifest();
    else if (get_git_super_project())
        return fetch_git_super_project();

    // Here we can't be sure, either it's a google manifest, a esysrepo manifest or a git super project
    return fetch_unknown_manifest();
}

int CmdInit::fetch_google_manifest()
{
    return -1;
}

int CmdInit::fetch_esysrepo_manifest()
{
    return -1;
}

int CmdInit::fetch_git_super_project()
{
    return -1;
}

int CmdInit::fetch_unknown_manifest()
{
    if (get_git() == nullptr) return -1;

    boost::filesystem::path path = get_config_folder()->get_temp_path();
    path /= "unknown_manifest";

    if (get_url().empty()) return -1;

    int result = get_git()->clone(get_url(), path.normalize().make_preferred().string());
    if (result < 0) return -1;

    if (!get_branch().empty())
    {
        result = get_git()->checkout(get_branch(), get_force());
        if (result < 0) return -1;
    }

    result = get_git()->close();
    if (result < 0) return -1;

    boost::filesystem::path file_path = path;
    file_path /= ".esysrepo.manifest";

    if (boost::filesystem::exists(file_path))
    {
        get_config_folder()->get_or_new_config()->set_manifest_type(manifest::Type::ESYSREPO_MANIFEST);

        boost::filesystem::path source = path.string();
        boost::filesystem::path target = get_config_folder()->get_parent_path();

        result = move(source.string(), target.string());
        if (result < -2) return -1;
        return 0;
    }

    file_path = path;
    if (!get_manifest_name().empty())
        file_path /= get_manifest_name();
    else
        file_path /= "default.xml";

    if (boost::filesystem::exists(file_path))
    {
        get_config_folder()->get_or_new_config()->set_manifest_type(manifest::Type::GOOGLE_MANIFEST);

        boost::filesystem::path source = path.string();
        boost::filesystem::path target = get_config_folder()->get_path();
        target /= "grepo";

        bool result_bool = boost::filesystem::create_directory(target);
        if (!result_bool) return -1;

        result = boost_no_all::move(source.string(), target.string());
        if (result == -1) return result;
        if (result == -2)
        {
            std::cout << "WARNING: while moving folder " << source << " some files were left behind." << std::endl;
        }
        std::string manifest_path = "grepo/";
        if (!get_manifest_name().empty())
            manifest_path += get_manifest_name();
        else
            manifest_path += "default.xml";

        get_config_folder()->get_config()->set_manifest_path(manifest_path);
        return get_config_folder()->write_config_file();
    }

    file_path = path;
    file_path /= ".gitmodules";

    if (boost::filesystem::exists(file_path))
    {
        get_config_folder()->get_or_new_config()->set_manifest_type(manifest::Type::GIT_SUPER_PROJECT);

        boost::filesystem::path source = path.string();
        boost::filesystem::path target = get_config_folder()->get_parent_path();

        result = move(source.string(), target.string());
        if (result < -1) return -1;
        return 0;
    }

    return -1;
}

int CmdInit::create_esysrepo_folder()
{
    auto config_folder = std::make_shared<ConfigFolder>();

    set_config_folder(config_folder);

    return config_folder->create(get_parent_path());
}

} // namespace exe

} // namespace repo

} // namespace esys