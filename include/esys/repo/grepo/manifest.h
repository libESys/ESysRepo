/*!
 * \file esys/repo/grepo/manifest.h
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

#include <memory>

namespace esys
{

namespace repo
{

namespace grepo
{

class ESYSREPO_API ManifestImpl;

class ESYSREPO_API Manifest
{
public:
    Manifest();
    virtual ~Manifest();

    int read(const std::string &filename);
    int write(const std::string &filename);

    void set_data(std::shared_ptr<repo::Manifest> data);
    std::shared_ptr<repo::Manifest> get_data();
    const std::shared_ptr<repo::Manifest> get_data() const;

    ManifestImpl *get_impl();

protected:
    std::unique_ptr<ManifestImpl> m_impl;
    std::shared_ptr<repo::Manifest> m_data;
};

} // namespace grepo

} // namespace repo

} // namespace esys
