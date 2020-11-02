/*!
 * \file esys/repo/manifest/repository.h
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

#include <string>

namespace esys
{

namespace repo
{

namespace manifest
{

class ESYSREPO_API Location;

class ESYSREPO_API Repository
{
public:
    Repository();
    Repository(const std::string &name, const std::string &path);
    virtual ~Repository();

    void set_name(const std::string &name);
    const std::string &get_name() const;

    void set_path(const std::string &path);
    const std::string &get_path() const;

    void set_revision(const std::string &revision);
    const std::string get_revision() const;

    void set_location(const std::string &location_str);
    const std::string &get_location_str() const;

    void set_location(Location *location);
    Location *get_location() const;

protected:
    std::string m_name;
    std::string m_path;
    std::string m_revision;
    Location *m_location = nullptr;
    std::string m_location_str;
};

} // namespace manifest

} // namespace repo

} // namespace esys