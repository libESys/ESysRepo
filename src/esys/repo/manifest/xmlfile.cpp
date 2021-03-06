/*!
 * \file esys/repo/manifest/xmlfile_manifest.cpp
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
#include "esys/repo/manifest/xmlfile.h"
#include "esys/repo/manifest/xmlfileimpl.h"

namespace esys::repo::manifest
{

XMLFile::XMLFile()
    : Base()
{
    m_impl = std::make_unique<XMLFileImpl>(this);
}

XMLFile::~XMLFile() = default;

Result XMLFile::read(const std::string &path)
{
    return get_impl()->read(path);
}

Result XMLFile::write(const std::string &path)
{
    return get_impl()->write(path);
}

Result XMLFile::write(std::ostream &os)
{
    return get_impl()->write(os);
}

XMLFileImpl *XMLFile::get_impl()
{
    return m_impl.get();
}

const XMLFileImpl *XMLFile::get_impl() const
{
    return m_impl.get();
}

} // namespace esys::repo::manifest
