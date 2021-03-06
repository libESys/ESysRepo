/*!
 * \file esys/repo/grepo/manifestimpl.h
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

#pragma once

#include "esys/repo/esysrepo_defs.h"
#include "esys/repo/grepo/manifest.h"
#include "esys/repo/result.h"

#include <esysfile/xml/data.h>
#include <esysfile/xml/file.h>

#include <deque>

namespace esys
{

namespace repo
{

namespace grepo
{

class ESYSREPO_API ManifestImpl
{
public:
    explicit ManifestImpl(Manifest *self);
    virtual ~ManifestImpl();

    Result read(const std::string &filename);
    Result write(const std::string &filename);
    Result write(std::ostream &os);

    void write_remotes();
    static void write_remote(std::shared_ptr<esysfile::xml::Element> parent,
                             std::shared_ptr<manifest::Location> location);
    static void write_default(std::shared_ptr<esysfile::xml::Element> parent, std::shared_ptr<repo::Manifest> manifest);
    [[nodiscard]] Result write_projects();
    Result write_project(std::shared_ptr<esysfile::xml::Element> parent, std::shared_ptr<manifest::Repository> repository);

    Result read(std::shared_ptr<esysfile::xml::Data> data);
    Result read(std::shared_ptr<esysfile::xml::Element> el);
    Result read_remote(std::shared_ptr<esysfile::xml::Element> el);
    Result read_default(std::shared_ptr<esysfile::xml::Element> el);
    Result read_groups(std::shared_ptr<manifest::Repository> project, const std::string &groups_str);
    Result read_project(std::shared_ptr<esysfile::xml::Element> el);
    Result read_include(std::shared_ptr<esysfile::xml::Element> el);

    Manifest *self() const;

protected:
    Result write_xml();

private:
    Manifest *m_self = nullptr;
    std::shared_ptr<esysfile::xml::Data> m_xml_data;
    std::shared_ptr<esysfile::xml::File> m_file;
    std::deque<std::shared_ptr<manifest::Repository>> m_repo_no_locations;
};

} // namespace grepo

} // namespace repo

} // namespace esys
