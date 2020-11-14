/*!
 * \file esys/repo/manifest/fetchbase.h
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
#include "esys/repo/config.h"
#include "esys/repo/configfolder.h"

#include <memory>

namespace esys
{

namespace repo
{

namespace manifest
{

class ESYSREPO_API FetchBase
{
public:
    FetchBase();
    virtual ~FetchBase();

    void set_manifest(std::shared_ptr<Manifest> manifest);
    std::shared_ptr<Manifest> get_manifest();
    const std::shared_ptr<Manifest> get_manifest() const;

    void set_config(std::shared_ptr<Config> config);
    std::shared_ptr<Config> get_config();
    const std::shared_ptr<Config> get_config() const;

    void set_config_folder(std::shared_ptr<ConfigFolder> config_folder);
    std::shared_ptr<ConfigFolder> get_config_folder();
    const std::shared_ptr<ConfigFolder> get_config_folder() const;

    virtual int run() = 0;
protected:
    std::shared_ptr<Manifest> m_manifest;
    std::shared_ptr<Config> m_config;
    std::shared_ptr<ConfigFolder> m_config_folder;
};

} // namespace manifest

} // namespace repo

} // namespace esys
