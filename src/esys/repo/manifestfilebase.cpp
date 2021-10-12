/*!
 * \file esys/repo/manifestfilebase.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2021 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/manifestfilebase.h"

namespace esys::repo
{

ManifestFileBase::ManifestFileBase() = default;

ManifestFileBase::~ManifestFileBase() = default;

void ManifestFileBase::set_data(std::shared_ptr<repo::Manifest> data)
{
    m_data = data;
}

std::shared_ptr<repo::Manifest> ManifestFileBase::get_data() const
{
    return m_data;
}

} // namespace esys::repo
