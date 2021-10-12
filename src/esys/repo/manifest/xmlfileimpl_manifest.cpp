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

namespace esys::repo::manifest
{

XMLFileImpl::XMLFileImpl(XMLFile *self)
    : m_self(self)
{
}

XMLFileImpl::~XMLFileImpl() = default;

int XMLFileImpl::read(const std::string &path)
{
    esysfile::xml::File xml_file;

    xml_file.set_root_node_name("esysrepo_manifest");
    int result = xml_file.read(path);
    if (result < 0)
    {
        self()->add_error(result, "XML parsing failed.");
        return result;
    }

    if (self()->get_data() == nullptr) self()->set_data(std::make_shared<Manifest>());

    self()->get_data()->set_type(Type::ESYSREPO_MANIFEST);

    return read(xml_file.get_data());
}

int XMLFileImpl::read(std::shared_ptr<esysfile::xml::Data> data)
{
    if (data->get_attrs().size() != 0)
    {
        int result = read_root_attributes(data);
        if (result < 0)
        {
            self()->add_error(result, "read_root_attributes failed.");
            return result;
        }
    }
    else
        self()->get_data()->set_kind(manifest::Kind::ISOLATED);

    int result = 0;

    for (auto el : data->get_elements())
    {
        if (el->get_name() == "location")
            result = read_location(el);
        else if ((el->get_name() == "default"))
            result = read_default(el);
        else if ((el->get_name() == "group"))
            result = read_group(el);
        else
            result = -1;
        if (result < 0)
        {
            self()->add_error(result, "Reading XML element failed : " + el->get_name());
            return result;
        }
    }
    return 0;
}

int XMLFileImpl::read_root_attributes(std::shared_ptr<esysfile::xml::Element> root_el)
{
    for (auto attr : root_el->get_attrs())
    {
        int result = read_root_attribute(attr);
        if (result < 0) return result;
    }
    return 0;
}

int XMLFileImpl::read_root_attribute(std::shared_ptr<esysfile::xml::Attr> attr)
{
    if (attr->get_name() != "kind") return -1;

    manifest::Kind kind;
    int result = convert(attr->get_value(), kind);
    if (result < 0) return -1;
    self()->get_data()->set_kind(kind);
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

    attr = el->get_attr("alt_addr");
    if (attr != nullptr) location->set_alt_address(attr->get_value());

    int result = 0;

    for (auto child_el : el->get_elements())
    {
        if (child_el->get_name() == "repository")
            result = read_repository(child_el, location);
        else
            result = -1;
        if (result < 0) return result;
    }

    self()->get_data()->add_location(location);
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
    if (el->get_name() != "default") return -1;

    for (auto attr : el->get_attrs())
    {
        int result = read_default_attr(attr);
        if (result < 0) return result;
    }
    return 0;
}

int XMLFileImpl::read_default_attr(std::shared_ptr<esysfile::xml::Attr> attr)
{
    if (attr->get_name() == "revision")
        self()->get_data()->set_default_revision(attr->get_value());
    else if (attr->get_name() == "sync-j")
        self()->get_data()->set_default_job_count(atoi(attr->get_value().c_str()));
    else
        return -1;
    return 0;
}

int XMLFileImpl::read_group(std::shared_ptr<esysfile::xml::Element> el)
{
    auto attr = el->get_attr("name");
    if (attr == nullptr) return -1;

    std::shared_ptr<Group> group = std::make_shared<Group>();
    group->set_name(attr->get_value());

    for (auto child : el->get_elements())
    {
        int result = read_group_repo(child, group);
        if (result < 0) return result;
    }

    self()->get_data()->get_groups().add_group(group);

    return 0;
}

int XMLFileImpl::read_group_repo(std::shared_ptr<esysfile::xml::Element> el, std::shared_ptr<Group> group)
{
    if (el->get_name() != "repo") return -1;

    auto attr = el->get_attr("path");
    if (attr == nullptr) return -2;

    auto repo = self()->get_data()->find_repo_by_path(attr->get_value());
    if (repo == nullptr) return -3;

    group->add_repo(repo);
    return 0;
}

int XMLFileImpl::write_xml()
{
    if (self()->get_data() == nullptr) return -1;

    m_xml_data = std::make_shared<esysfile::xml::Data>();
    m_xml_data->set_root_node_name("esysrepo_manifest");

    if (self()->get_data()->get_kind() != manifest::Kind::ISOLATED)
    {
        std::string kind;
        int result = convert(self()->get_data()->get_kind(), kind);
        if (result < 0) return result;
        m_xml_data->add_attr("kind", kind);
    }

    for (auto location : self()->get_data()->get_locations())
    {
        int result = write(m_xml_data, location);
        if (result < 0) return result;
    }

    for (auto group : self()->get_data()->get_groups().get_groups())
    {
        int result = write(m_xml_data, group);
        if (result < 0) return result;
    }
    return 0;
}

int XMLFileImpl::write(const std::string &path)
{
    if (write_xml() < 0) return -1;

    esysfile::xml::Writer writer;

    writer.set_indent(4);
    return writer.write(path, m_xml_data);
}

int XMLFileImpl::write(std::ostream &os)
{
    if (write_xml() < 0) return -1;

    esysfile::xml::Writer writer;

    writer.set_indent(4);
    return writer.write(os, m_xml_data);
}

int XMLFileImpl::write(std::shared_ptr<esysfile::xml::Element> parent_el, std::shared_ptr<Location> location)
{
    std::shared_ptr<esysfile::xml::Element> location_el = std::make_shared<esysfile::xml::Element>();

    location_el->set_name("location");
    location_el->add_attr("name", location->get_name());
    location_el->add_attr("addr", location->get_address());

    for (auto repo : location->get_repos())
    {
        int result = write(location_el, repo);
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

int XMLFileImpl::write(std::shared_ptr<esysfile::xml::Element> parent_el, std::shared_ptr<Group> group)
{
    std::shared_ptr<esysfile::xml::Element> grp_el = std::make_shared<esysfile::xml::Element>();

    grp_el->set_name("group");
    grp_el->add_attr("name", group->get_name());

    for (auto repo : group->get_repos())
    {
        std::shared_ptr<esysfile::xml::Element> repo_el = std::make_shared<esysfile::xml::Element>();

        repo_el->set_name("repo");
        repo_el->add_attr("path", repo->get_path());
        grp_el->add_element(repo_el);
    }

    parent_el->add_element(grp_el);
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

} // namespace esys::repo::manifest
