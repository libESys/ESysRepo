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
#include "esys/repo/githelper.h"

#include <boost/filesystem.hpp>

#include <iostream>

namespace esys
{

namespace repo
{

namespace exe
{

CmdInit::CmdInit()
    : Cmd("Init")
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

std::string CmdInit::get_extra_start_msg()
{
    return "\n    url : " + get_url();
}

int CmdInit::impl_run()
{
    int result;

    if (get_google_manifest()) warn("The option --google is not implemented yet");
    if (get_git_super_project()) warn("The option --git-super is not implemented yet");

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

    info("Detecting the manifest type ...");

    boost::filesystem::path path = get_config_folder()->get_temp_path();
    path /= "unknown_manifest";

    if (get_url().empty())
    {
        error("URL is empty");
        return -1;
    }

    GitHelper git_helper(get_git(), get_logger_if());

    int result = git_helper.clone(get_url(), path.normalize().make_preferred().string(), false, log::DEBUG);
    if (result < 0) return -1;

    if (!get_branch().empty())
    {
        result = get_git()->checkout(get_branch() /*, get_force()*/);
        if (result < 0) return -1;
    }

    result = git_helper.close(log::DEBUG);
    if (result < 0) return -1;

    boost::filesystem::path file_path = path;
    file_path /= ".esysrepo.manifest";

    if (boost::filesystem::exists(file_path))
    {
        info("ESysRepo manifest detected.");
        get_config_folder()->get_or_new_config()->set_manifest_type(manifest::Type::ESYSREPO_MANIFEST);

        boost::filesystem::path source = path.string();
        boost::filesystem::path rel_source = boost::filesystem::relative(source);
        boost::filesystem::path target = get_config_folder()->get_parent_path();

        result = git_helper.move(source.string(), target.string(), true, log::Level::DEBUG);
        if (result == -1) return result;
        if (result == -2) warn("While moving folder " + rel_source.string() + " some files were left behind.");

        return 0;
    }

    file_path = path;
    if (!get_manifest_name().empty())
        file_path /= get_manifest_name();
    else
        file_path /= "default.xml";

    if (boost::filesystem::exists(file_path))
    {
        info("Google repo tool manifest detected.");
        get_config_folder()->get_or_new_config()->set_manifest_type(manifest::Type::GOOGLE_MANIFEST);

        boost::filesystem::path source = path.string();
        boost::filesystem::path rel_source = boost::filesystem::relative(source);
        boost::filesystem::path target = get_config_folder()->get_path();
        boost::filesystem::path rel_target = boost::filesystem::relative(target);
        target /= "grepo";
        rel_target = boost::filesystem::relative(target);

        bool result_bool = boost::filesystem::create_directory(target);
        if (!result_bool)
        {
            error("Couldn't create the folder : " + rel_target.string());
            return -1;
        }
        else
            debug(0, "Created folder : " + rel_target.string());

        result = git_helper.move(source.string(), target.string(), true, log::Level::DEBUG);
        if (result == -1) return result;
        if (result == -2) warn("While moving folder " + rel_source.string() + " some files were left behind.");

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
        info("Git submodule detected.");
        get_config_folder()->get_or_new_config()->set_manifest_type(manifest::Type::GIT_SUPER_PROJECT);

        boost::filesystem::path source = path.string();
        boost::filesystem::path target = get_config_folder()->get_parent_path();

        result = git_helper.move(source.string(), target.string(), true, log::Level::DEBUG);
        if (result < -1) return -1;
        return 0;
    }

    return -1;
}

int CmdInit::create_esysrepo_folder()
{
    auto config_folder = std::make_shared<ConfigFolder>();
    config_folder->set_logger_if(get_logger_if());

    set_config_folder(config_folder);

    return config_folder->create(get_parent_path());
}

} // namespace exe

} // namespace repo

} // namespace esys