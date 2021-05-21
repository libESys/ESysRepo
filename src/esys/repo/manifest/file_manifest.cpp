/*!
 * \file esys/repo/manifest/file_manifest.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2021 Michel Gillet
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

void File::set_data(std::shared_ptr<Manifest> data)
{
    m_data = data;
}

std::shared_ptr<Manifest> File::get_data()
{
    return m_data;
}

const std::shared_ptr<Manifest> File::get_data() const
{
    return m_data;
}

} // namespace manifest

} // namespace repo

} // namespace esys
