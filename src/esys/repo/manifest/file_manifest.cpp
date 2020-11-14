/*!
 * \file esys/repo/manifest/file_manifest.cpp
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
#include "esys/repo/manifest/file.h"

namespace esys
{

namespace repo
{

namespace manifest
{

File::File() = default;

File::~File() = default;

void File::set_manifest(std::shared_ptr<Manifest> manifest)
{
    m_manifest = manifest;
}

std::shared_ptr<Manifest> File::get_manifest()
{
    return m_manifest;
}

const std::shared_ptr<Manifest> File::get_manifest() const
{
    return m_manifest;
}

} // namespace manifest

} // namespace repo

} // namespace esys
