/*!
 * \file esys/repo/exe/cmdinit.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2022 Michel Gillet
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
#include "esys/repo/git/url.h"
#include "esys/repo/manifest/file.h"
#include "esys/repo/manifest/xmlfile.h"
#include "esys/repo/grepo/manifest.h"

#include <boost/filesystem.hpp>

#include <cassert>
#include <iostream>
#include <sstream>

namespace esys::repo::exe
{

CmdInit::CmdInit()
    : Cmd("Init")
{
}

CmdInit::~CmdInit() = default;

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

Result CmdInit::impl_run()
{
    if (get_google_manifest()) warn("The option --google is not implemented yet");
    if (get_git_super_project()) warn("The option --git-super is not implemented yet");

    Result result = only_one_folder_or_workspace();
    if (result.error()) return ESYSREPO_RESULT(result);

    result = load_esysrepo_folder();
    if (result.ok()) return load_esysrepo_folder_succeeded();
    return load_esysrepo_folder_failed();
}

Result CmdInit::load_esysrepo_folder_succeeded()
{
    assert(get_config_folder() != nullptr);
    if (get_config_folder() == nullptr)
    {
        error("Internal error [CmdInit::load_esysrepo_folder_succeeded] get_config_folder() == nullptr");
        return ESYSREPO_RESULT(ResultCode::INTERNAL_ERROR);
    }

    auto config = get_config_folder()->get_config();
    assert(config != nullptr);
    if (config == nullptr)
    {
        error("Internal error [CmdInit::load_esysrepo_folder_succeeded] config == nullptr");
        return ESYSREPO_RESULT(ResultCode::INTERNAL_ERROR);
    }

    git::URL url(get_url());
    if (url != config->get_manifest_url())
    {
        std::stringstream oss;

        oss << "Current manifest url is:" << std::endl;
        oss << "    " << config->get_manifest_url() << std::endl;
        oss << "But manifest url given is different:" << std::endl;
        oss << "    " << get_url() << std::endl;
        oss << "Use --force if this is really wanted.";
        error(oss.str());
        return ESYSREPO_RESULT(ResultCode::CMD_INCORRECT_PARAMETERS_IN_CONTEXT, oss.str());
    }

    if (get_branch().empty())
    {
        warn("Nothing to do as a branch is not provided");
        return ESYSREPO_RESULT(ResultCode::OK);
    }

    boost::filesystem::path manifest_git_path = get_config_folder()->get_manifest_repo_path();

    auto git_helper = new_git_helper();

    debug(1, "Test debug, before git_helper");
    git_helper->debug(1, "Test debug with git_helper");

    Result result = git_helper->open(manifest_git_path.normalize().make_preferred().string(), log::DEBUG);
    if (result.error())
    {
        std::string err_str = "Opening git repo holding the manifest failed.";
        error(err_str);
        return ESYSREPO_RESULT(result, err_str);
    }

    result = get_git()->checkout(get_branch() /*, get_force()*/);
    if (result.error())
    {
        std::string err_str = "Checkout branch failed.";
        error(err_str);
        return ESYSREPO_RESULT(result, err_str);
    }

    get_git()->close();

    return ESYSREPO_RESULT(ResultCode::OK);
}

Result CmdInit::load_esysrepo_folder_failed()
{
    // Since it failed, either there is no .esysrepo folder or the xml config
    // file is corrupted
    Result result = create_esysrepo_folder();
    if (result.error()) return ESYSREPO_RESULT(result);

    // Now there are 2 cases, we couldn't load be the ESysRepo config folder because
    // it got corrupted, or it's not there at all.
    result = fetch_manifest();
    if (result.error()) return ESYSREPO_RESULT(result);

    return ESYSREPO_RESULT(ResultCode::OK);
}

Result CmdInit::fetch_manifest()
{
    if (get_google_manifest())
        return fetch_google_manifest();
    else if (get_git_super_project())
        return fetch_git_super_project();

    // Here we can't be sure, either it's a google manifest, a esysrepo manifest or a git super project
    return fetch_unknown_manifest();
}

Result CmdInit::fetch_google_manifest()
{
    return ESYSREPO_RESULT(ResultCode::NOT_IMPLEMENTED);
}

Result CmdInit::read_esysrepo_manifest(std::shared_ptr<Manifest> manifest, const std::string &filename)
{
    manifest::File manifest_file;

    manifest_file.set_data(manifest);
    Result result = manifest_file.read(filename);
    return ESYSREPO_RESULT(result);
}

Result CmdInit::read_esysrepo_manifest_xml(std::shared_ptr<Manifest> manifest, const std::string &filename)
{
    manifest::XMLFile manifest_file;

    manifest_file.set_data(manifest);
    Result result = manifest_file.read(filename);
    return ESYSREPO_RESULT(result);
}

Result CmdInit::read_esysrepo_manifest_json(std::shared_ptr<Manifest> manifest, const std::string &filename)
{
    //! \TODO
    return ESYSREPO_RESULT(ResultCode::NOT_IMPLEMENTED);
}

Result CmdInit::fetch_esysrepo_manifest(GitHelper &git_helper, const std::string &git_repo_path,
                                        const std::string &manifest_filename)
{
    std::string manifest_path;
    boost::filesystem::path manifest_filename_path = manifest_filename;
    std::string manifest_filename_ext = manifest_filename_path.extension().string();

    info("ESysRepo manifest detected.");
    debug(0, "Manifest filename : " + manifest_filename);

    auto config_file = get_config_folder()->get_or_new_config();

    config_file->set_manifest_type(manifest::Type::ESYSREPO_MANIFEST);
    config_file->set_manifest_url(get_url());

    boost::filesystem::path source = git_repo_path;
    boost::filesystem::path rel_source = boost::filesystem::relative(source);
    boost::filesystem::path target;
    boost::filesystem::path file_path = git_repo_path;
    file_path /= manifest_filename;

    std::shared_ptr<Manifest> manifest = std::make_shared<Manifest>();

    if (manifest_filename_ext == ".manifest")
    {
        Result result = read_esysrepo_manifest(manifest, file_path.string());
        if (result.error()) return ESYSREPO_RESULT(result);
    }
    else if (manifest_filename_ext == ".xml")
    {
        Result result = read_esysrepo_manifest_xml(manifest, file_path.string());
        if (result.error()) return ESYSREPO_RESULT(result);
        manifest->set_format(manifest::Format::XML);
        config_file->set_manifest_format(manifest::Format::XML);
    }
    else if (manifest_filename_ext == ".json")
    {
        Result result = read_esysrepo_manifest_json(manifest, file_path.string());
        if (result.error()) return ESYSREPO_RESULT(result);
        manifest->set_format(manifest::Format::JSON);
        config_file->set_manifest_format(manifest::Format::JSON);
    }
    else
    {
        return ESYSREPO_RESULT(ResultCode::MANIFEST_FILE_EXT_UNKNOWN, manifest_filename_ext);
    }

    config_file->set_manifest_format(manifest->get_format());

    if (manifest->get_kind() == manifest::Kind::NOT_SET) manifest->set_kind(manifest::Kind::ISOLATED);

    if (manifest->get_kind() == manifest::Kind::EMBEDDED)
    {
        info("Embedded kind.");
        config_file->set_manifest_kind(manifest::Kind::EMBEDDED);
        target = get_config_folder()->get_workspace_path();
        Result result = git_helper.move(source.string(), target.string(), true, log::Level::DEBUG);
        if (result == ResultCode::FAILED_TO_COPY) return ESYSREPO_RESULT(result);
        if (result == ResultCode::FAILED_TO_REMOVE_ALL)
            warn("While moving folder " + rel_source.string() + " some files were left behind.");
        target = "..";
        target /= manifest_filename;
        manifest_path = target.string();
    }
    else if (manifest->get_kind() == manifest::Kind::ISOLATED)
    {
        info("Isolated kind.");
        config_file->set_manifest_kind(manifest::Kind::ISOLATED);
        target = get_config_folder()->get_path();

        target /= manifest::Base::get_folder_name();
        boost::filesystem::path rel_target;
        rel_target = boost::filesystem::relative(target);

        bool result_bool = boost::filesystem::create_directory(target);
        if (!result_bool)
        {
            error("Couldn't create the folder : " + rel_target.string());
            return ESYSREPO_RESULT(ResultCode::FOLDER_CREATION_ERROR, target.string());
        }
        else
            debug(0, "Created folder : " + rel_target.string());

        Result result = git_helper.move(source.string(), target.string(), true, log::Level::DEBUG);
        if (result == ResultCode::FAILED_TO_COPY) return ESYSREPO_RESULT(result);
        if (result == ResultCode::FAILED_TO_REMOVE_ALL)
            warn("While moving folder " + rel_source.string() + " some files were left behind.");
        target = manifest::Base::get_folder_name();
        target /= manifest_filename;
        manifest_path = target.generic().string();
    }
    else
        return ESYSREPO_RESULT(ResultCode::MANIFEST_KIND_UNKNOWN);

    config_file->set_manifest_path(manifest_path);
    Result result = get_config_folder()->write_config_file();
    return ESYSREPO_RESULT(result);
}

Result CmdInit::fetch_git_super_project()
{
    return ESYSREPO_RESULT(ResultCode::NOT_IMPLEMENTED);
}

Result CmdInit::fetch_unknown_manifest()
{
    if (get_git() == nullptr) return ESYSREPO_RESULT(ResultCode::INTERNAL_ERROR);

    info("Detecting the manifest type ...");

    boost::filesystem::path path = get_config_folder()->get_temp_path();
    path /= "unknown_manifest";

    if (get_url().empty())
    {
        error("URL is empty");
        return ESYSREPO_RESULT(ResultCode::CMDINIT_NO_URL);
    }

    auto git_helper = new_git_helper();

    debug(1, "Test debug, before git_helper");
    git_helper->debug(1, "Test debug with git_helper");

    Result result = git_helper->clone(get_url(), path.normalize().make_preferred().string(), false, log::DEBUG);
    if (result.error())
    {
        error("Cloning failed.");
        return ESYSREPO_RESULT(result);
    }

    if (!get_branch().empty())
    {
        result = get_git()->checkout(get_branch() /*, get_force()*/);
        if (result.error())
        {
            std::string err_str = "Cloning failed : checkout branch failed.";
            error(err_str);
            return ESYSREPO_RESULT(result, err_str);
        }
    }

    result = git_helper->close(log::DEBUG);
    if (result.error())
    {
        std::string err_str = "Cloning failed : can't clod the git repo.";
        error(err_str);
        return ESYSREPO_RESULT(result, err_str);
    }

    boost::filesystem::path file_path = path;
    file_path /= ".esysrepo.manifest";

    if (boost::filesystem::exists(file_path))
    {
        result = fetch_esysrepo_manifest(*git_helper.get(), path.string(), ".esysrepo.manifest");
        return ESYSREPO_RESULT(result);
    }

    file_path = path;
    file_path /= ".esysrepo.manifest.xml";

    if (boost::filesystem::exists(file_path))
    {
        result = fetch_esysrepo_manifest(*git_helper.get(), path.string(), ".esysrepo.manifest.xml");
        return ESYSREPO_RESULT(result);
    }

    file_path = path;
    file_path /= ".esysrepo.manifest.json";

    if (boost::filesystem::exists(file_path))
    {
        result = fetch_esysrepo_manifest(*git_helper.get(), path.string(), ".esysrepo.manifest.json");
        return ESYSREPO_RESULT(result);
    }
    file_path = path;
    if (!get_manifest_name().empty())
        file_path /= get_manifest_name();
    else
        file_path /= "default.xml";

    if (boost::filesystem::exists(file_path))
    {
        info("Google repo tool manifest detected.");
        auto config = get_config_folder()->get_or_new_config();
        config->set_manifest_type(manifest::Type::GOOGLE_MANIFEST);
        config->set_manifest_format(manifest::Format::XML);
        config->set_manifest_url(get_url());

        boost::filesystem::path source = path.string();
        boost::filesystem::path rel_source = boost::filesystem::relative(source);
        boost::filesystem::path target = get_config_folder()->get_path();
        boost::filesystem::path rel_target = boost::filesystem::relative(target);
        target /= grepo::Manifest::get_folder_name();
        rel_target = boost::filesystem::relative(target);

        bool result_bool = boost::filesystem::create_directory(target);
        if (!result_bool)
        {
            std::string err_str = "Couldn't create the folder : " + rel_target.string();
            error(err_str);
            return ESYSREPO_RESULT(ResultCode::FOLDER_CREATION_ERROR, err_str);
        }
        else
            debug(0, "Created folder : " + rel_target.string());

        result = git_helper->move(source.string(), target.string(), true, log::Level::DEBUG);
        if (result == ResultCode::FAILED_TO_COPY) return ESYSREPO_RESULT(result);
        if (result == ResultCode::FAILED_TO_REMOVE_ALL)
            warn("While moving folder " + rel_source.string() + " some files were left behind.");

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
        auto config = get_config_folder()->get_or_new_config();

        config->set_manifest_type(manifest::Type::GIT_SUPER_PROJECT);
        config->set_manifest_url(get_url());
        boost::filesystem::path source = path.string();
        boost::filesystem::path target = get_config_folder()->get_workspace_path();

        result = git_helper->move(source.string(), target.string(), true, log::Level::DEBUG);
        if (result == ResultCode::FAILED_TO_COPY) return ESYSREPO_RESULT(result);
        if (result == ResultCode::FAILED_TO_REMOVE_ALL)
            warn("While moving folder " + source.string() + " some files were left behind.");
        return ESYSREPO_RESULT(ResultCode::OK);
    }

    return ESYSREPO_RESULT(ResultCode::CMDINIT_FAILED_FETCH_UNKNOWN_MANIFEST);
}

Result CmdInit::load_esysrepo_folder()
{
    debug(0, "[CmdInit::load_esysrepo_folder] begin ...");

    auto config_folder = std::make_shared<ConfigFolder>();
    config_folder->set_logger_if(get_logger_if());

    set_config_folder(config_folder);

    debug(0, "[CmdInit::load_esysrepo_folder] parent_path = " + get_workspace_path());

    Result result = config_folder->open(get_workspace_path(), false);
    debug(0, "[CmdInit::create_esysrepo_folder] end.");
    return ESYSREPO_RESULT(result);
}

Result CmdInit::create_esysrepo_folder()
{
    debug(0, "[CmdInit::create_esysrepo_folder] begin ...");

    auto config_folder = get_config_folder();
    if (config_folder == nullptr)
    {
        config_folder = std::make_shared<ConfigFolder>();
        config_folder->set_logger_if(get_logger_if());

        set_config_folder(config_folder);
    }

    debug(0, "[CmdInit::create_esysrepo_folder] parent_path = " + get_workspace_path());

    Result result = config_folder->create(get_workspace_path(), true);
    debug(0, "[CmdInit::create_esysrepo_folder] end.");
    return ESYSREPO_RESULT(result);
}

} // namespace esys::repo::exe
