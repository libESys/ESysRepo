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

    Result read(const std::string &path);
    int write(const std::string &path);
    int write(std::ostream &os);

    Result read(std::shared_ptr<esysfile::xml::Data> data);
    Result read_root_attributes(std::shared_ptr<esysfile::xml::Element> root_el);
    Result read_root_attribute(std::shared_ptr<esysfile::xml::Attr> attr);
    Result read_location(std::shared_ptr<esysfile::xml::Element> el);
    static Result read_repository(std::shared_ptr<esysfile::xml::Element> el, std::shared_ptr<Location> location);
    Result read_default(std::shared_ptr<esysfile::xml::Element> el);
    Result read_default_attr(std::shared_ptr<esysfile::xml::Attr> attr);
    Result read_group(std::shared_ptr<esysfile::xml::Element> el);
    Result read_group_repo(std::shared_ptr<esysfile::xml::Element> el, std::shared_ptr<Group> group);

    static int write(std::shared_ptr<esysfile::xml::Element> parent_el, std::shared_ptr<Location> location);
    static int write(std::shared_ptr<esysfile::xml::Element> parent_el, std::shared_ptr<Repository> repository);
    static int write(std::shared_ptr<esysfile::xml::Element> parent_el, std::shared_ptr<Group> group);

    XMLFile *self();
    const XMLFile *self() const;

protected:
    int write_xml();

private:
    XMLFile *m_self = nullptr;
    std::shared_ptr<esysfile::xml::Data> m_xml_data;
};

} // namespace manifest

} // namespace repo

} // namespace esys
