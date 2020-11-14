/*!
 * \file esys/repo/exe/cmdsync.h
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

class ESYSREPO_API CmdSync
{
public:
    CmdSync();
    virtual ~CmdSync();

    void set_parent_path(const std::string &parent_path);
    const std::string &get_parent_path() const;

    void set_manifest(std::shared_ptr<Manifest> manifest);
    std::shared_ptr<Manifest> get_manifest();
    const std::shared_ptr<Manifest> get_manifest() const;

    void set_config_folder(std::shared_ptr<ConfigFolder> config_folder);
    std::shared_ptr<ConfigFolder> get_config_folder();
    const std::shared_ptr<ConfigFolder> get_config_folder() const;

    void set_fetcher(std::shared_ptr<manifest::Fetch> fetcher);
    std::shared_ptr<manifest::Fetch> get_fetcher();
    const std::shared_ptr<manifest::Fetch> get_fetcher() const;

    void set_git(std::shared_ptr<GitBase> git);
    std::shared_ptr<GitBase> get_git();
    const std::shared_ptr<GitBase> get_git() const;

    int run();

    int open_esysrepo_folder();

protected:
    std::string m_parent_path;
    std::shared_ptr<Manifest> m_manifest;
    std::shared_ptr<manifest::Fetch> m_fetcher;
    std::shared_ptr<ConfigFolder> m_config_folder;
    std::shared_ptr<GitBase> m_git;
};

} // namespace exe

} // namespace repo

} // namespace esys