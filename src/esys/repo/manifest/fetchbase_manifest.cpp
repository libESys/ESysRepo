/*!
 * \file esys/repo/manifest/fetchbase_manifest.cpp
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
#include "esys/repo/manifest/fetchbase.h"

namespace esys
{

namespace repo
{

namespace manifest
{

FetchBase::FetchBase() = default;

FetchBase::~FetchBase() = default;

void FetchBase::set_manifest(std::shared_ptr<Manifest> manifest)
{
    m_manifest = manifest;
}

std::shared_ptr<Manifest> FetchBase::get_manifest()
{
    return m_manifest;
}

const std::shared_ptr<Manifest> FetchBase::get_manifest() const
{
    return m_manifest;
}

void FetchBase::set_config(std::shared_ptr<Config> config)
{
    m_config = config;
}

std::shared_ptr<Config> FetchBase::get_config()
{
    return m_config;
}

const std::shared_ptr<Config> FetchBase::get_config() const
{
    return m_config;
}

void FetchBase::set_config_folder(std::shared_ptr<ConfigFolder> config_folder)
{
    m_config_folder = config_folder;
}

std::shared_ptr<ConfigFolder> FetchBase::get_config_folder()
{
    return m_config_folder;
}

const std::shared_ptr<ConfigFolder> FetchBase::get_config_folder() const
{
    return m_config_folder;
}

} // namespace manifest

} // namespace repo

} // namespace esys
