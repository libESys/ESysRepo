/*!
 * \file esys/repo/exe/cmd.cpp
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
#include "esys/repo/exe/cmd.h"
#include "esys/repo/filesystem.h"
#include "esys/repo/configfolder.h"

#include <boost/filesystem.hpp>

namespace esys
{

namespace repo
{

namespace exe
{

Cmd::Cmd()
    : log::User()
{
}

Cmd::~Cmd() = default;

void Cmd::set_manifest(std::shared_ptr<Manifest> manifest)
{
    m_manifest = manifest;
}

std::shared_ptr<Manifest> Cmd::get_manifest()
{
    return m_manifest;
}

const std::shared_ptr<Manifest> Cmd::get_manifest() const
{
    return m_manifest;
}

void Cmd::set_git(std::shared_ptr<GitBase> git)
{
    m_git = git;
}

std::shared_ptr<GitBase> Cmd::get_git()
{
    return m_git;
}

const std::shared_ptr<GitBase> Cmd::get_git() const
{
    return m_git;
}

void Cmd::set_parent_path(const std::string &parent_path)
{
    m_parent_path = parent_path;
}

const std::string &Cmd::get_parent_path() const
{
    return m_parent_path;
}

std::string Cmd::find_parent_path(const std::string &path)
{
    boost::filesystem::path cur_path;

    if (!path.empty())
        cur_path = path;
    else
        cur_path = boost::filesystem::current_path();

    while (!cur_path.empty())
    {
        if (ConfigFolder::is_config_folder(cur_path.string())) return cur_path.string();
        cur_path = cur_path.parent_path();
    }

    return "";
}

void Cmd::set_debug(bool debug)
{
    m_debug = debug;
}

bool Cmd::get_debug() const
{
    return m_debug;
}

int Cmd::set_folder(const std::string &folder)
{
    if (!folder.empty())
    {
        boost::filesystem::path path = folder;
        path = boost::filesystem::absolute(path).normalize().make_preferred();
        set_parent_path(path.string());
    }
    else
    {
        boost::filesystem::path path = esys::repo::exe::Cmd::find_parent_path();
        if (path.empty())
        {
            error("Couldn't find a folder with esysrepo from : " + boost::filesystem::current_path().string());
            return -1;
        }
        set_parent_path(path.string());
    }
    return 0;
}

void Cmd::set_config_folder(std::shared_ptr<ConfigFolder> config_folder)
{
    m_config_folder = config_folder;
}

std::shared_ptr<ConfigFolder> Cmd::get_config_folder()
{
    return m_config_folder;
}

const std::shared_ptr<ConfigFolder> Cmd::get_config_folder() const
{
    return m_config_folder;
}

void Cmd::set_loader(std::shared_ptr<manifest::Loader> loader)
{
    m_loader = loader;
}

std::shared_ptr<manifest::Loader> Cmd::get_loader()
{
    return m_loader;
}

const std::shared_ptr<manifest::Loader> Cmd::get_loader() const
{
    return m_loader;
}

int Cmd::open_esysrepo_folder()
{
    auto config_folder = std::make_shared<ConfigFolder>();

    set_config_folder(config_folder);

    boost::filesystem::path rel_parent_path = boost::filesystem::relative(get_parent_path());
    int result = config_folder->open(get_parent_path());
    if (result < 0)
        error("Failed to open esysrepo folder : " + rel_parent_path.string());
    else
        debug(0, "Opened esysrepo folder : " + rel_parent_path.string());

    return result;
}

int Cmd::load_manifest()
{
    int result = open_esysrepo_folder();
    if (result < 0) return result;

    if (get_loader() == nullptr) set_loader(std::make_shared<manifest::Loader>());
    if (get_manifest() == nullptr) set_manifest(std::make_shared<Manifest>());

    get_loader()->set_manifest(get_manifest());
    get_loader()->set_config_folder(get_config_folder());

    get_loader()->set_logger_if(get_logger_if());
    result = get_loader()->run();
    return result;
}

} // namespace exe

} // namespace repo

} // namespace esys