/*!
 * \file esys/repo/manifest/file.h
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

#include <string>
#include <memory>

namespace esys
{

namespace repo
{

namespace manifest
{

class ESYSREPO_API File
{
public:
    File();
    virtual ~File();

    void set_manifest(std::shared_ptr<Manifest> manifest);
    std::shared_ptr<Manifest> get_manifest();
    const std::shared_ptr<Manifest> get_manifest() const;

    virtual int read(const std::string &path) = 0;
    virtual int write(const std::string &path) = 0;

protected:
    std::shared_ptr<Manifest> m_manifest;
};

} // namespace manifest

} // namespace repo

} // namespace esys
