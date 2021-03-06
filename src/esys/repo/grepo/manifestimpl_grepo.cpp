/*!
 * \file esys/repo/grepo/manifestimpl_grepo.cpp
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
#include "esys/repo/grepo/manifestimpl.h"
#include "esys/repo/grepo/manifest.h"
#include "esys/repo/manifest/repository.h"

#include <esysfile/xml/writer.h>
#include <esysfile/xml/attr.h>

#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>

namespace esys::repo::grepo
{

ManifestImpl::ManifestImpl(Manifest *self)
    : m_self(self)
{
}

ManifestImpl::~ManifestImpl() = default;

Result ManifestImpl::read(const std::string &filename)
{
    m_repo_no_locations.clear();

    m_file = std::make_shared<esysfile::xml::File>();
    m_file->set_root_node_name("manifest");

    if (self()->get_data() == nullptr) self()->set_data(std::make_shared<repo::Manifest>());

    self()->get_data()->clear();

    int result = m_file->read(filename);
    if (result < 0) return ESYSREPO_RESULT(ResultCode::MANIFEST_ERROR_PARSING_FILE, filename);

    self()->get_data()->set_type(manifest::Type::GOOGLE_MANIFEST);
    self()->get_data()->set_kind(manifest::Kind::ISOLATED);

    return read(m_file->get_data());
}

Result ManifestImpl::write_xml()
{
    if (self()->get_data() == nullptr) return ESYSREPO_RESULT(ResultCode::MANIFEST_XML_DATA_NULLPTR);

    m_xml_data = std::make_shared<esysfile::xml::Data>();

    m_xml_data->set_root_node_name("manifest");

    write_remotes();
    write_default(m_xml_data, self()->get_data());
    Result result = write_projects();
    return ESYSREPO_RESULT(result);
}

Result ManifestImpl::write(const std::string &filename)
{
    Result result = write_xml();
    if (result.error()) return ESYSREPO_RESULT(result);

    esysfile::xml::Writer writer;

    writer.set_data(m_xml_data);

    int result_int = writer.write(filename);
    if (result_int < 0) return ESYSREPO_RESULT(ResultCode::RAW_INT_ERROR, result_int);
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result ManifestImpl::write(std::ostream &os)
{
    Result result = write_xml();
    if (write_xml().error()) return ESYSREPO_RESULT(result);

    esysfile::xml::Writer writer;

    writer.set_indent(4);
    writer.set_data(m_xml_data);

    int result_int = writer.write(os);
    if (result_int < 0) return ESYSREPO_RESULT(ResultCode::RAW_INT_ERROR, result_int);
    return ESYSREPO_RESULT(ResultCode::OK);
}

void ManifestImpl::write_remotes()
{
    for (auto &remote : self()->get_data()->get_locations())
    {
        write_remote(m_xml_data, remote);
    }
}

void ManifestImpl::write_remote(std::shared_ptr<esysfile::xml::Element> parent,
                                std::shared_ptr<manifest::Location> location)
{
    std::shared_ptr<esysfile::xml::Element> remote_el;

    remote_el = std::make_shared<esysfile::xml::Element>();

    remote_el->set_name("remote");
    remote_el->add_attr("name", location->get_name());
    remote_el->add_attr("fetch", location->get_address());

    parent->add_element(remote_el);
}

void ManifestImpl::write_default(std::shared_ptr<esysfile::xml::Element> parent,
                                 std::shared_ptr<repo::Manifest> manifest)
{
    std::shared_ptr<esysfile::xml::Element> default_el;

    default_el = std::make_shared<esysfile::xml::Element>();

    default_el->set_name("default");
    if (!manifest->get_default_revision().empty()) default_el->add_attr("revision", manifest->get_default_revision());
    if (manifest->get_default_location()) default_el->add_attr("remote", manifest->get_default_location()->get_name());
    if (manifest->get_default_job_count() != 1) default_el->add_attr("sync-j", manifest->get_default_job_count());

    parent->add_element(default_el);
}

Result ManifestImpl::write_projects()
{
    for (auto &remote : self()->get_data()->get_locations())
    {
        for (auto &project : remote->get_repos())
        {
            Result result = write_project(m_xml_data, project);
            if (result.error()) return ESYSREPO_RESULT(result);
        }
    }
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result ManifestImpl::write_project(std::shared_ptr<esysfile::xml::Element> parent,
                                   std::shared_ptr<manifest::Repository> repository)
{
    std::shared_ptr<esysfile::xml::Element> project_el;

    project_el = std::make_shared<esysfile::xml::Element>();

    project_el->set_name("project");

    if (repository->get_path().empty()) return ESYSREPO_RESULT(ResultCode::MANIFEST_REPOSITORY_WITHOUT_PATH);
    project_el->add_attr("path", repository->get_path());

    if (repository->get_location() == nullptr) return ESYSREPO_RESULT(ResultCode::MANIFEST_REPOSITORY_WITHOUT_LOCATION);

    bool add_location = true;

    if (self()->get_data()->get_default_location() != nullptr)
    {
        if (repository->get_location()->get_name() == self()->get_data()->get_default_location()->get_name())
            add_location = false;
    }
    if (add_location) project_el->add_attr("remote", repository->get_location()->get_name());

    if (repository->get_name().empty()) return ESYSREPO_RESULT(ResultCode::MANIFEST_REPOSITORY_WITHOUT_NAME);
    project_el->add_attr("name", repository->get_name());

    if (!repository->get_revision().empty()) project_el->add_attr("revision", repository->get_revision());

    auto &groups = repository->get_groups();
    if (groups.size() != 0)
    {
        std::string groups_str;

        for (auto group : groups)
        {
            if (groups_str.size() != 0) groups_str += ",";

            groups_str += group->get_name();
        }

        project_el->add_attr("groups", groups_str);
    }

    parent->add_element(project_el);
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result ManifestImpl::read(std::shared_ptr<esysfile::xml::Data> data)
{
    std::shared_ptr<manifest::Location> location;

    for (auto element : data->get_elements())
    {
        Result result = read(element);
        if (result.error()) return ESYSREPO_RESULT(result);
    }

    for (auto it = m_repo_no_locations.begin(); it != m_repo_no_locations.end();)
    {
        location = self()->get_data()->find_location((*it)->get_name());
        if (location != nullptr)
        {
            location->add_repo(*it);
            m_repo_no_locations.erase(it);
        }
        else
            ++it;
    }

    if (m_repo_no_locations.size() != 0) return ESYSREPO_RESULT(ResultCode::MANIFEST_NO_LOCATIONS_DEFINED);
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result ManifestImpl::read(std::shared_ptr<esysfile::xml::Element> el)
{
    Result result;

    if (el->get_name() == "remote")
        result = read_remote(el);
    else if (el->get_name() == "default")
        result = read_default(el);
    else if (el->get_name() == "project")
        result = read_project(el);
    else if (el->get_name() == "include")
        result = read_include(el);
    else if (el->get_name() != "#comment")
    {
        return ESYSREPO_RESULT(ResultCode::MANIFEST_ELEMENT_UNKNOWN, el->get_name());
    }
    return ESYSREPO_RESULT(result);
}

Result ManifestImpl::read_remote(std::shared_ptr<esysfile::xml::Element> el)
{
    auto location = std::make_shared<manifest::Location>();

    for (auto attr : el->get_attrs())
    {
        if (attr->get_name() == "name")
            location->set_name(attr->get_value());
        else if (attr->get_name() == "fetch")
            location->set_address(attr->get_value());
        else
        {
            return ESYSREPO_RESULT(ResultCode::MANIFEST_ATTRIBUTE_UNKNOWN, el->get_name() + ": " + attr->get_name());
        }
    }

    self()->get_data()->add_location(location);

    return ESYSREPO_RESULT(ResultCode::OK);
}

Result ManifestImpl::read_default(std::shared_ptr<esysfile::xml::Element> el)
{
    for (auto attr : el->get_attrs())
    {
        if (attr->get_name() == "revision")
            self()->get_data()->set_default_revision(attr->get_value());
        else if (attr->get_name() == "remote")
            self()->get_data()->set_default_location(attr->get_value());
        else if (attr->get_name() == "sync-j")
        {
            int value = 0;
            int result = attr->get_value(value);
            if (result < 0)
                return ESYSREPO_RESULT(ResultCode::MANIFEST_INCORRECT_ATTRIBUTE_VALUE,
                                       el->get_name() + "." + attr->get_name());
            self()->get_data()->set_default_job_count(value);
        }
        else
        {
            return ESYSREPO_RESULT(ResultCode::MANIFEST_ATTRIBUTE_UNKNOWN, el->get_name() + ": " + attr->get_name());
        }
    }
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result ManifestImpl::read_groups(std::shared_ptr<manifest::Repository> project, const std::string &groups_str)
{
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> sep(", ");
    tokenizer tokens(groups_str, sep);

    for (tokenizer::iterator it = tokens.begin(); it != tokens.end(); ++it)
    {
        auto group = self()->get_data()->get_groups().find_or_new_group_by_name(*it);
        project->get_groups().push_back(group.get());
        group->add_repo(project);
    }
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result ManifestImpl::read_project(std::shared_ptr<esysfile::xml::Element> el)
{
    auto project = std::make_shared<manifest::Repository>();
    bool remote_found = false;

    for (auto attr : el->get_attrs())
    {
        if (attr->get_name() == "name")
            project->set_name(attr->get_value());
        else if (attr->get_name() == "remote")
        {
            remote_found = true;
            auto location = self()->get_data()->find_location(attr->get_value());
            if (location != nullptr)
                location->add_repo(project);
            else
            {
                project->set_location(attr->get_value());
                m_repo_no_locations.push_back(project);
            }
        }
        else if (attr->get_name() == "path")
            project->set_path(attr->get_value());
        else if (attr->get_name() == "revision")
            project->set_revision(attr->get_value());
        else if (attr->get_name() == "groups")
        {
            Result result = read_groups(project, attr->get_value());
            //! \TODO handle errors
        }
        else
        {
            return ESYSREPO_RESULT(ResultCode::MANIFEST_ATTRIBUTE_UNKNOWN, el->get_name() + ": " + attr->get_name());
        }
    }

    if (!remote_found)
    {
        // It means that the default remote is to be used.
        if (self()->get_data()->get_default_location() != nullptr)
            self()->get_data()->get_default_location()->add_repo(project);
        else
            return ESYSREPO_RESULT(ResultCode::MANIFEST_NO_DEFAULT_LOCATION);
    }

    return ESYSREPO_RESULT(ResultCode::OK);
}

Result ManifestImpl::read_include(std::shared_ptr<esysfile::xml::Element> el)
{
    if (el->get_name() != "include") return ESYSREPO_RESULT(ResultCode::INTERNAL_ERROR);

    auto include = std::make_shared<manifest::Include>();
    std::string name;
    std::string value;

    for (auto attr : el->get_attrs())
    {
        name = attr->get_name();
        value = attr->get_value();
        if (name == "name")
        {
            if (boost::filesystem::exists(value))
            {
                include->set_name(value);
            }
            else
            {
                // Here we assume that the include is relative to the folder "manifests"
                boost::filesystem::path full_path = self()->get_filename();
                boost::filesystem::path rel_path = "manifests";
                full_path = full_path.parent_path();
                rel_path /= value;
                full_path /= rel_path;

                if (boost::filesystem::exists(full_path))
                    include->set_name(full_path.string());
                else
                {
                    // TBD: ERROR
                }
            }
        }
    }
    self()->get_data()->add_include(include);
    return ESYSREPO_RESULT(ResultCode::OK);
}

Manifest *ManifestImpl::self() const
{
    return m_self;
}

} // namespace esys::repo::grepo
