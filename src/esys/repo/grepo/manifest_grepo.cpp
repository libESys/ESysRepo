/*!
 * \file esys/repo/grepo/manifest_grepo.cpp
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
#include "esys/repo/grepo/manifest.h"
#include "esys/repo/grepo/manifestimpl.h"

namespace esys
{

namespace repo
{

namespace grepo
{

const std::string Manifest::s_folder_name = "grepo";

const std::string &Manifest::get_folder_name()
{
    return s_folder_name;
}

Manifest::Manifest()
    : manifest::FileBase()
{
    m_impl = std::make_unique<ManifestImpl>(this);
}

Manifest::~Manifest()
{
}

int Manifest::read(const std::string &filename)
{
    return m_impl->read(filename);
}

int Manifest::write(const std::string &filename)
{
    return m_impl->write(filename);
}

int Manifest::write(std::ostream &os)
{
    return m_impl->write(os);
}

bool Manifest::operator==(const Manifest &other) const
{
    return (*get_data() == *other.get_data());
}

bool Manifest::operator!=(const Manifest &other) const
{
    return !operator==(other);
}

ManifestImpl *Manifest::get_impl()
{
    return m_impl.get();
}

ESYSREPO_API std::ostream &operator<<(std::ostream &os, const Manifest &manifest)
{
    return os;
}

} // namespace grepo

} // namespace repo

} // namespace esys
