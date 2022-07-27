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

Result XMLFileImpl::read(const std::string &path)
{
    esysfile::xml::File xml_file;

    xml_file.set_root_node_name("esysrepo_manifest");
    int result = xml_file.read(path);
    if (result < 0)
    {
        self()->add_error(result, "XML parsing failed.");
        return ESYSREPO_RESULT(ResultCode::MANIFEST_ERROR_PARSING_FILE, path);
    }

    if (self()->get_data() == nullptr) self()->set_data(std::make_shared<Manifest>());

    self()->get_data()->set_type(Type::ESYSREPO_MANIFEST);

    return read(xml_file.get_data());
}

Result XMLFileImpl::read(std::shared_ptr<esysfile::xml::Data> data)
{
    if (data->get_attrs().size() != 0)
    {
        Result result = read_root_attributes(data);
        if (result.error())
        {
            self()->add_error(result.get_result_code_int(), "read_root_attributes failed.");
            return ESYSREPO_RESULT(result);
        }
    }
    else
        self()->get_data()->set_kind(manifest::Kind::ISOLATED);

    Result result;

    for (auto el : data->get_elements())
    {
        if (el->get_name() == "location")
            result = read_location(el);
        else if ((el->get_name() == "default"))
            result = read_default(el);
        else if ((el->get_name() == "group"))
            result = read_group(el);
        else
            result = ESYSREPO_RESULT(ResultCode::MANIFEST_ELEMENT_UNKNOWN, el->get_name());
        if (result.error())
        {
            self()->add_error(result.get_result_code_int(), "Reading XML element failed : " + el->get_name());
            return result;
        }
    }
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result XMLFileImpl::read_root_attributes(std::shared_ptr<esysfile::xml::Element> root_el)
{
    for (auto attr : root_el->get_attrs())
    {
        Result result = read_root_attribute(attr);
        if (result.error()) return ESYSREPO_RESULT(result);
    }
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result XMLFileImpl::read_root_attribute(std::shared_ptr<esysfile::xml::Attr> attr)
{
    if (attr->get_name() != "kind") return ESYSREPO_RESULT(ResultCode::INTERNAL_ERROR);

    manifest::Kind kind;
    Result result = convert(attr->get_value(), kind);
    if (result.error()) return ESYSREPO_RESULT(result, ResultCode::MANIFEST_KIND_UNKNOWN, attr->get_value());

    self()->get_data()->set_kind(kind);
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result XMLFileImpl::read_location(std::shared_ptr<esysfile::xml::Element> el)
{
    if (el->get_name() != "location") return ESYSREPO_RESULT(ResultCode::INTERNAL_ERROR);

    std::shared_ptr<Location> location = std::make_shared<Location>();

    auto attr = el->get_attr("name");
    if (attr != nullptr)
        location->set_name(attr->get_value());
    else
        return ESYSREPO_RESULT(ResultCode::MANIFEST_LOCATION_WITHOUT_NAME);

    attr = el->get_attr("addr");
    if (attr != nullptr)
        location->set_address(attr->get_value());
    else
        return ESYSREPO_RESULT(ResultCode::MANIFEST_LOCATION_WITHOUT_ADDRESS);

    attr = el->get_attr("alt_addr");
    if (attr != nullptr) location->set_alt_address(attr->get_value());

    Result result;

    for (auto child_el : el->get_elements())
    {
        if (child_el->get_name() == "repository")
            result = read_repository(child_el, location);
        else
            result = ESYSREPO_RESULT(ResultCode::MANIFEST_ELEMENT_UNKNOWN, child_el->get_name());
        if (result.error()) return result;
    }

    self()->get_data()->add_location(location);
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result XMLFileImpl::read_repository(std::shared_ptr<esysfile::xml::Element> el, std::shared_ptr<Location> location)
{
    if (el->get_name() != "repository") return ESYSREPO_RESULT(ResultCode::INTERNAL_ERROR);

    auto repository = std::make_shared<Repository>();
    repository->set_location(location.get());

    auto attr = el->get_attr("name");
    if (attr == nullptr) return ESYSREPO_RESULT(ResultCode::MANIFEST_REPOSITORY_WITHOUT_NAME);
    repository->set_name(attr->get_value());

    attr = el->get_attr("path");
    if (attr == nullptr) return ESYSREPO_RESULT(ResultCode::MANIFEST_REPOSITORY_WITHOUT_PATH);
    repository->set_path(attr->get_value());

    attr = el->get_attr("revision");
    if (attr != nullptr) repository->set_revision(attr->get_value());

    location->add_repo(repository);

    return ESYSREPO_RESULT(ResultCode::OK);
}

Result XMLFileImpl::read_default(std::shared_ptr<esysfile::xml::Element> el)
{
    if (el->get_name() != "default") return ESYSREPO_RESULT(ResultCode::INTERNAL_ERROR);

    for (auto attr : el->get_attrs())
    {
        Result result = read_default_attr(attr);
        if (result.error()) return result;
    }
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result XMLFileImpl::read_default_attr(std::shared_ptr<esysfile::xml::Attr> attr)
{
    if (attr->get_name() == "revision")
        self()->get_data()->set_default_revision(attr->get_value());
    else if (attr->get_name() == "sync-j")
        self()->get_data()->set_default_job_count(atoi(attr->get_value().c_str()));
    else
        return ESYSREPO_RESULT(ResultCode::MANIFEST_ATTRIBUTE_UNKNOWN, attr->get_name());
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result XMLFileImpl::read_group(std::shared_ptr<esysfile::xml::Element> el)
{
    auto attr = el->get_attr("name");
    if (attr == nullptr) return ESYSREPO_RESULT(ResultCode::MANIFEST_GROUP_WITHOUT_NAME);

    std::shared_ptr<Group> group = std::make_shared<Group>();
    group->set_name(attr->get_value());

    for (auto child : el->get_elements())
    {
        Result result = read_group_repo(child, group);
        if (result.error()) return ESYSREPO_RESULT(result);
    }

    self()->get_data()->get_groups().add_group(group);

    return ESYSREPO_RESULT(ResultCode::OK);
}

Result XMLFileImpl::read_group_repo(std::shared_ptr<esysfile::xml::Element> el, std::shared_ptr<Group> group)
{
    if (el->get_name() != "repo") return ESYSREPO_RESULT(ResultCode::MANIFEST_GROUP_REPO_WITHOUT_NAME);

    auto attr = el->get_attr("path");
    if (attr == nullptr) return ESYSREPO_RESULT(ResultCode::MANIFEST_GROUP_REPO_WITHOUT_PATH);

    auto repo = self()->get_data()->find_repo_by_path(attr->get_value());
    if (repo == nullptr) return ESYSREPO_RESULT(ResultCode::MANIFEST_REPO_UNKNOWN, "path = " + attr->get_value());

    group->add_repo(repo);
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result XMLFileImpl::write_xml()
{
    if (self()->get_data() == nullptr) return ESYSREPO_RESULT(ResultCode::MANIFEST_XML_DATA_NULLPTR);

    m_xml_data = std::make_shared<esysfile::xml::Data>();
    m_xml_data->set_root_node_name("esysrepo_manifest");

    if (self()->get_data()->get_kind() != manifest::Kind::ISOLATED)
    {
        std::string kind;
        Result result = convert(self()->get_data()->get_kind(), kind);
        if (result.error()) return ESYSREPO_RESULT(result);
        m_xml_data->add_attr("kind", kind);
    }

    for (auto location : self()->get_data()->get_locations())
    {
        Result result = write(m_xml_data, location);
        if (result.error()) return ESYSREPO_RESULT(result);
    }

    for (auto group : self()->get_data()->get_groups().get_groups())
    {
        Result result = write(m_xml_data, group);
        if (result.error()) return ESYSREPO_RESULT(result);
    }
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result XMLFileImpl::write(const std::string &path)
{
    Result result = write_xml();
    if (result.error()) return ESYSREPO_RESULT(result);

    esysfile::xml::Writer writer;

    writer.set_indent(4);
    int result_int = writer.write(path, m_xml_data);
    if (result_int < 0) return ESYSREPO_RESULT(ResultCode::RAW_INT_ERROR, result_int);
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result XMLFileImpl::write(std::ostream &os)
{
    Result result = write_xml();
    if (result.error()) return ESYSREPO_RESULT(result);

    esysfile::xml::Writer writer;

    writer.set_indent(4);
    int result_int = writer.write(os, m_xml_data);
    if (result_int < 0) return ESYSREPO_RESULT(ResultCode::RAW_INT_ERROR, result_int);
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result XMLFileImpl::write(std::shared_ptr<esysfile::xml::Element> parent_el, std::shared_ptr<Location> location)
{
    std::shared_ptr<esysfile::xml::Element> location_el = std::make_shared<esysfile::xml::Element>();

    location_el->set_name("location");
    location_el->add_attr("name", location->get_name());
    location_el->add_attr("addr", location->get_address());

    for (auto repo : location->get_repos())
    {
        Result result = write(location_el, repo);
        if (result.error()) return ESYSREPO_RESULT(result);
    }

    parent_el->add_element(location_el);
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result XMLFileImpl::write(std::shared_ptr<esysfile::xml::Element> parent_el, std::shared_ptr<Repository> repository)
{
    std::shared_ptr<esysfile::xml::Element> repo_el = std::make_shared<esysfile::xml::Element>();

    repo_el->set_name("repository");
    repo_el->add_attr("path", repository->get_path());
    repo_el->add_attr("name", repository->get_name());
    if (!repository->get_revision().empty()) repo_el->add_attr("revision", repository->get_revision());

    parent_el->add_element(repo_el);
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result XMLFileImpl::write(std::shared_ptr<esysfile::xml::Element> parent_el, std::shared_ptr<Group> group)
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
    return ESYSREPO_RESULT(ResultCode::OK);
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
