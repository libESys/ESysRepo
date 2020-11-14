/*!
 * \file esys/repo/manifest/clonerepos.h
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
#include "esys/repo/manifest.h"
#include "esys/repo/configfolder.h"
#include "esys/repo/manifest/repository.h"
#include "esys/repo/gitbase.h"

#include <memory>

namespace esys
{

namespace repo
{

namespace manifest
{

class ESYSREPO_API CloneRepos
{
public:
    CloneRepos();
    virtual ~CloneRepos();

    void set_manifest(std::shared_ptr<Manifest> manifest);
    std::shared_ptr<Manifest> get_manifest();
    const std::shared_ptr<Manifest> get_manifest() const;

    void set_config_folder(std::shared_ptr<ConfigFolder> config_folder);
    std::shared_ptr<ConfigFolder> get_config_folder();
    const std::shared_ptr<ConfigFolder> get_config_folder() const;

    void set_git(std::shared_ptr<GitBase> git);
    std::shared_ptr<GitBase> get_git();
    const std::shared_ptr<GitBase> get_git() const;

    virtual int run();

    virtual int clone(std::shared_ptr<manifest::Repository> repository);

protected:
    std::shared_ptr<Manifest> m_manifest;
    std::shared_ptr<ConfigFolder> m_config_folder;
    std::shared_ptr<GitBase> m_git;
};

} // namespace manifest

} // namespace repo

} // namespace esys
