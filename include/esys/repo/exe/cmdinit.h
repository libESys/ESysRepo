/*!
 * \file esys/repo/exe/cmdinit.h
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

#pragma once

#include "esys/repo/esysrepo_defs.h"
#include "esys/repo/manifest/type.h"
#include "esys/repo/manifest/fetch.h"
#include "esys/repo/configfolder.h"
#include "esys/repo/gitbase.h"

#include <string>
#include <vector>
#include <memory>

namespace esys
{

namespace repo
{

namespace exe
{

class ESYSREPO_API CmdInit
{
public:
    CmdInit();
    virtual ~CmdInit();

    void set_url(const std::string &url);
    const std::string &get_url() const;

    void set_branch(const std::string &branch);
    const std::string &get_branch() const;

    void set_manifest_name(const std::string &manifest_name);
    const std::string &get_manifest_name() const;

    void set_google_manifest(bool google_manifest);
    bool get_google_manifest() const;

    void set_git_super_project(bool git_super_project);
    bool get_git_super_project() const;

    void set_parent_path(const std::string &parent_path);
    const std::string &get_parent_path() const;

    void set_force(bool force);
    bool get_force() const;

    void set_manifest(std::shared_ptr<Manifest> manifest);
    std::shared_ptr<Manifest> get_manifest();
    const std::shared_ptr<Manifest> get_manifest() const;

    void set_fetcher(std::shared_ptr<manifest::Fetch> fetcher);
    std::shared_ptr<manifest::Fetch> get_fetcher();
    const std::shared_ptr<manifest::Fetch> get_fetcher() const;

    void set_config_folder(std::shared_ptr<ConfigFolder> config_folder);
    std::shared_ptr<ConfigFolder> get_config_folder();
    const std::shared_ptr<ConfigFolder> get_config_folder() const;

    void set_git(std::shared_ptr<GitBase> git);
    std::shared_ptr<GitBase> get_git();
    const std::shared_ptr<GitBase> get_git() const;

    int run();

    int fetch_manifest();
    int fetch_google_manifest();
    int fetch_esysrepo_manifest();
    int fetch_git_super_project();
    int fetch_unknown_manifest();
    int create_esysrepo_folder();

protected:
    std::string m_url;
    std::string m_branch;
    std::string m_manifest_name;
    bool m_google_manifest = false;
    bool m_git_super_project = false;
    std::string m_parent_path;
    bool m_force = false;
    manifest::Type m_manifest_type = manifest::Type::NOT_SET;
    std::shared_ptr<Manifest> m_manifest;
    std::shared_ptr<manifest::Fetch> m_fetcher;
    std::shared_ptr<ConfigFolder> m_config_folder;
    std::shared_ptr<GitBase> m_git;
};

} // namespace exe

} // namespace repo

} // namespace esys