/*!
 * \file esys/repo/manifest.h
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
#include "esys/repo/manifest/type.h"
#include "esys/repo/manifest/location.h"

#include <string>
#include <vector>
#include <memory>
#include <map>

namespace esys
{

namespace repo
{

class ESYSREPO_API Manifest
{
public:
    Manifest();
    virtual ~Manifest();

    void set_type(manifest::Type type);
    manifest::Type get_type() const;

    int add_location(std::shared_ptr<manifest::Location> location, bool is_default = false);
    std::vector<std::shared_ptr<manifest::Location>> &get_locations();
    const std::vector<std::shared_ptr<manifest::Location>> &get_locations() const;

    std::map<std::string, std::shared_ptr<manifest::Location>> &get_map_locations();
    const std::map<std::string, std::shared_ptr<manifest::Location>> &get_map_locations() const;

    std::shared_ptr<manifest::Location> find_location(const std::string &name);

    void set_default_location(std::shared_ptr<manifest::Location> default_location);
    std::shared_ptr<manifest::Location> get_default_location();
    const std::shared_ptr<manifest::Location> get_default_location() const;

    void set_default_location(const std::string &default_location_str);
    const std::string &get_default_location_str() const;

    void set_default_revision(const std::string &default_revision);
    const std::string get_default_revision() const;

    void set_default_job_count(int default_job_count);
    int get_default_job_count() const;

protected:
    manifest::Type m_type = manifest::Type::NOT_SET;
    std::vector<std::shared_ptr<manifest::Location>> m_locations;
    std::map<std::string, std::shared_ptr<manifest::Location>> m_map_locations;
    std::shared_ptr<manifest::Location> m_default_location;
    std::string m_default_location_str;
    std::string m_default_revision = "master";
    int m_default_job_count = 1;
};

} // namespace repo

} // namespace esys