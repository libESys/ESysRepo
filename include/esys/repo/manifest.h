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

//<swig_inc/>

namespace esys
{

namespace repo
{

/*! \class Manifest esys/repo/manifest.h "esys/repo/manifest.h"
 * \brief Hold the data of a generalized manifest
 */
class ESYSREPO_API Manifest
{
public:
    //! Default contructor
    Manifest();

    //! Destructor
    virtual ~Manifest();

    //! Set the type of manifest
    /*!
     * \param[in] type the type of manifest
     */
    void set_type(manifest::Type type);

    //! Get the type of manifest
    /*!
     * \return the type of manifest
     */
    manifest::Type get_type() const;

    //! Add a location to the manifest
    /*!
     * \param[in] location the location
     * \param[in] is_default true if it's the default location of this manifest
     */
    int add_location(std::shared_ptr<manifest::Location> location, bool is_default = false);

    //! Get all locations of this manifest
    /*!
     * \return all locations of this manifest
     */
    std::vector<std::shared_ptr<manifest::Location>> &get_locations();

    //! Get all locations of this manifest
    /*!
     * \return all locations of this manifest
     */
    const std::vector<std::shared_ptr<manifest::Location>> &get_locations() const;

    //! Get the map of all locations of this manifest
    /*!
     * \return the map all locations of this manifest
     */
    std::map<std::string, std::shared_ptr<manifest::Location>> &get_map_locations();

    //! Get the map of all locations of this manifest
    /*!
     * \return the map all locations of this manifest
     */
    const std::map<std::string, std::shared_ptr<manifest::Location>> &get_map_locations() const;

    //! Find a location by its name
    /*!
     * \param[in] name the name of the location to find
     * \return the location if found, nullptr otherwise
     */
    std::shared_ptr<manifest::Location> find_location(const std::string &name);

    //! Find a git repo by its path
    /*!
     * \param[in] path the path of the git repo to find
     * \return the location if found, nullptr otherwise
     */
    std::shared_ptr<manifest::Repository> find_repo_by_path(const std::string &path);

    //! Set the default location
    /*!
     * \param[in] default_location the default location
     */
    void set_default_location(std::shared_ptr<manifest::Location> default_location);

    //! Get the default location
    /*!
     * \return the default location
     */
    std::shared_ptr<manifest::Location> get_default_location();

    //! Get the default location
    /*!
     * \return the default location
     */
    const std::shared_ptr<manifest::Location> get_default_location() const;

    //! Set the name of the default location
    /*!
     * \param[in] default_location_str the name of the default location
     */
    void set_default_location(const std::string &default_location_str);

    //! Get the name of the default location
    /*!
     * \return the name of the default location
     */
    const std::string &get_default_location_str() const;

    //! Set the default revision
    /*!
     * \param[in] default_revision the default revision
     */
    void set_default_revision(const std::string &default_revision);

    //! Get the default revision
    /*!
     * \return the default revision
     */
    const std::string get_default_revision() const;

    //! Set the default job count
    /*!
     * \param[in] default_job_count the default job count
     */
    void set_default_job_count(int default_job_count);

    //! Get the default job count
    /*!
     * \return the default job count
     */
    int get_default_job_count() const;

    //! Get revision to use for a given repository
    /*!
     * \param[in] repo the repository
     * \return the revision to use for that repository
     */
    std::string get_repo_revision(std::shared_ptr<manifest::Repository> repo);

protected:
    //!< \cond DOXY_IMPL
    manifest::Type m_type = manifest::Type::NOT_SET;                            //!< The type of repository
    std::vector<std::shared_ptr<manifest::Location>> m_locations;               //!< All the locations
    std::map<std::string, std::shared_ptr<manifest::Location>> m_map_locations; //!< The map of all locations by name
    std::map<std::string, std::shared_ptr<manifest::Location>> m_map_locations_by_path; 
    std::shared_ptr<manifest::Location> m_default_location;                     //!< The default location
    std::string m_default_location_str;                                         //!< The name of the default location
    std::string m_default_revision = "master";                                  //!< The default revision
    int m_default_job_count = 1; //!< The default number of concurrent jobs
    //!< \endcond
};

} // namespace repo

} // namespace esys