/*!
 * \file esys/repo/manifest/xmlfileimpl_manifest.cpp
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
#include "esys/repo/manifest/xmlfileimpl.h"
#include "esys/repo/manifest/xmlfile.h"

#include <esysfile/xml/writer.h>
#include <esysfile/xml/file.h>
#include <esysfile/xml/attr.h>

namespace esys
{

namespace repo
{

namespace manifest
{

XMLFileImpl::XMLFileImpl(XMLFile *self)
    : m_self(self)
{
}

XMLFileImpl::~XMLFileImpl()
{
}

int XMLFileImpl::read(const std::string &path)
{
    esysfile::xml::File xml_file;

    xml_file.set_root_node_name("esysrepo_manifest");
    int result = xml_file.read(path);
    if (result < 0) return result;

    if (self()->get_manifest() == nullptr) self()->set_manifest(std::make_shared<Manifest>());

    self()->get_manifest()->set_type(Type::ESYSREPO_MANIFEST);

    return read(xml_file.get_data());
}

int XMLFileImpl::read(std::shared_ptr<esysfile::xml::Data> data)
{
    int result = 0;

    for (auto el : data->get_elements())
    {
        if (el->get_name() == "location")
            result = read_location(el);
        else if ((el->get_name() == "default"))
            result = read_default(el);
        else
            result = -1;
        if (result < 0) return result;
    }
    return 0;
}

int XMLFileImpl::read_location(std::shared_ptr<esysfile::xml::Element> el)
{
    if (el->get_name() != "location") return -1;

    std::shared_ptr<Location> location = std::make_shared<Location>();

    auto attr = el->get_attr("name");
    if (attr != nullptr)
        location->set_name(attr->get_value());
    else
        return -1;

    attr = el->get_attr("addr");
    if (attr != nullptr)
        location->set_address(attr->get_value());
    else
        return -1;

    int result;

    for (auto child_el : el->get_elements())
    {
        if (child_el->get_name() == "repository")
            result = read_repository(child_el, location);
        else
            result = -1;
        if (result < 0) return result;
    }

    self()->get_manifest()->add_location(location);
    return 0;
}

int XMLFileImpl::read_repository(std::shared_ptr<esysfile::xml::Element> el, std::shared_ptr<Location> location)
{
    if (el->get_name() != "repository") return -1;

    auto repository = std::make_shared<Repository>();
    repository->set_location(location.get());

    auto attr = el->get_attr("name");
    if (attr == nullptr) return -1;
    repository->set_name(attr->get_value());

    attr = el->get_attr("path");
    if (attr == nullptr) return -1;
    repository->set_path(attr->get_value());

    attr = el->get_attr("revision");
    if (attr != nullptr) repository->set_revision(attr->get_value());

    location->add_repo(repository);

    return 0;
}

int XMLFileImpl::read_default(std::shared_ptr<esysfile::xml::Element> el)
{
    return -1;
}

int XMLFileImpl::write(const std::string &path)
{
    if (self()->get_manifest() == nullptr) return -1;

    m_xml_data = std::make_shared<esysfile::xml::Data>();
    m_xml_data->set_root_node_name("esysrepo_manifest");

    int result;

    for (auto location : self()->get_manifest()->get_locations())
    {
        result = write(m_xml_data, location);
        if (result < 0) return result;
    }

    esysfile::xml::Writer writer;

    writer.set_indent(4);
    result = writer.write(path, m_xml_data);
    return result;
}

int XMLFileImpl::write(std::shared_ptr<esysfile::xml::Element> parent_el, std::shared_ptr<Location> location)
{
    std::shared_ptr<esysfile::xml::Element> location_el = std::make_shared<esysfile::xml::Element>();

    location_el->set_name("location");
    location_el->add_attr("name", location->get_name());
    location_el->add_attr("addr", location->get_address());

    int result;

    for (auto repo : location->get_repos())
    {
        result = write(location_el, repo);
        if (result < 0) return result;
    }

    parent_el->add_element(location_el);
    return 0;
}

int XMLFileImpl::write(std::shared_ptr<esysfile::xml::Element> parent_el, std::shared_ptr<Repository> repository)
{
    std::shared_ptr<esysfile::xml::Element> repo_el = std::make_shared<esysfile::xml::Element>();

    repo_el->set_name("repository");
    repo_el->add_attr("path", repository->get_path());
    repo_el->add_attr("name", repository->get_name());
    if (!repository->get_revision().empty()) repo_el->add_attr("revision", repository->get_revision());

    parent_el->add_element(repo_el);
    return 0;
}

XMLFile *XMLFileImpl::self()
{
    return m_self;
}

const XMLFile *XMLFileImpl::self() const
{
    return m_self;
}

} // namespace manifest

} // namespace repo

} // namespace esys
