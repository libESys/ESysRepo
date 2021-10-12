/*!
 * \file esys/repo/manifest/xmlfileimpl.h
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

#pragma once

#include "esys/repo/esysrepo_defs.h"
#include "esys/repo/manifest/xmlfile.h"
#include "esys/repo/manifest/location.h"
#include "esys/repo/manifest/repository.h"

#include <esysfile/xml/data.h>

#include <memory>

namespace esys
{

namespace repo
{

namespace manifest
{

class ESYSREPO_API XMLFileImpl
{
public:
    explicit XMLFileImpl(XMLFile *self);
    virtual ~XMLFileImpl();

    int read(const std::string &path);
    int write(const std::string &path);
    int write(std::ostream &os);

    int read(std::shared_ptr<esysfile::xml::Data> data);
    int read_root_attributes(std::shared_ptr<esysfile::xml::Element> root_el);
    int read_root_attribute(std::shared_ptr<esysfile::xml::Attr> attr);
    int read_location(std::shared_ptr<esysfile::xml::Element> el);
    int read_repository(std::shared_ptr<esysfile::xml::Element> el, std::shared_ptr<Location> location);
    int read_default(std::shared_ptr<esysfile::xml::Element> el);
    int read_default_attr(std::shared_ptr<esysfile::xml::Attr> attr);
    int read_group(std::shared_ptr<esysfile::xml::Element> el);
    int read_group_repo(std::shared_ptr<esysfile::xml::Element> el, std::shared_ptr<Group> group);

    int write(std::shared_ptr<esysfile::xml::Element> parent_el, std::shared_ptr<Location> location);
    int write(std::shared_ptr<esysfile::xml::Element> parent_el, std::shared_ptr<Repository> repository);
    int write(std::shared_ptr<esysfile::xml::Element> parent_el, std::shared_ptr<Group> group);

    XMLFile *self();
    const XMLFile *self() const;

protected:
    int write_xml();

    XMLFile *m_self = nullptr;
    std::shared_ptr<esysfile::xml::Data> m_xml_data;
};

} // namespace manifest

} // namespace repo

} // namespace esys
