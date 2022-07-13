/*!
 * \file esys/repo/manifest/include_manifest.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2022 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/manifest/include.h"

namespace esys::repo::manifest
{

Include::Include() = default;

Include::Include(const std::string &name)
    : m_name(name)
{
}

Include::~Include() = default;

void Include::set_name(const std::string &name)
{
    m_name = name;
}

const std::string &Include::get_name() const
{
    return m_name;
}

bool Include::operator==(const Include &other) const
{
    return get_name() == other.get_name();
}

bool Include::operator!=(const Include &other) const
{
    return !operator==(other);
}

} // namespace esys::repo::manifest
