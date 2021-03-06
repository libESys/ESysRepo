/*!
 * \file esys/repo/manifest.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2022 Michel Gillet
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
#include "esys/repo/manifest/kind.h"
#include "esys/repo/manifest/format.h"
#include "esys/repo/manifest/location.h"
#include "esys/repo/manifest/groups.h"
#include "esys/repo/manifest/include.h"

#include <memory>
#include <map>
#include <string>
#include <vector>

//<swig_inc/>

//<swig>%shared_ptr(esys::repo::Manifest);</swig>

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

    //! Set the kind of manifest
    /*!
     * \param[in] kind the kind of manifest
     */
    void set_kind(manifest::Kind kind);

    //! Get the kind of manifest
    /*!
     * \return the kind of manifest
     */
    manifest::Kind get_kind() const;

    //! Set the format of manifest
    /*!
     * \param[in] format the format of manifest
     */
    void set_format(manifest::Format format);

    //! Get the format of manifest
    /*!
     * \return the format of manifest
     */
    manifest::Format get_format() const;

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
    const std::vector<std::shared_ptr<manifest::Location>> &get_locations() const; //<swig_out/>

    //! Get the map of all locations of this manifest
    /*!
     * \return the map all locations of this manifest
     */
    std::map<std::string, std::shared_ptr<manifest::Location>> &get_map_locations();

    //! Get the map of all locations of this manifest
    /*!
     * \return the map all locations of this manifest
     */
    const std::map<std::string, std::shared_ptr<manifest::Location>> &get_map_locations() const; //<swig_out/>

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

    //! Find the path of a git repo identified by its url
    /*!
     * \param[in] git_repo_name the urlthe git repo to find
     * \return the path if found, empty string otherwise
     */
    std::string find_repo_path_by_url(const std::string &url);

    //! Find the reposotiry of a git repo identified by its url
    /*!
     * \param[in] url the url of the git repo to find
     * \return the repository if found, otherwise nullptr
     */
    std::shared_ptr<manifest::Repository> find_repo_by_url(const std::string &url);

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
    const std::string &get_default_revision() const;

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

    void clear();

    manifest::Groups &get_groups();
    const manifest::Groups &get_groups() const; //<swig_out/>

    //! Add an include to the manifest
    /*!
     * \param[in] location the location
     */
    void add_include(std::shared_ptr<manifest::Include> include);

    //! Get all includes of this manifest
    /*!
     * \return all includes of this manifest
     */
    std::vector<std::shared_ptr<manifest::Include>> &get_includes();

    //! Get all includes of this manifest
    /*!
     * \return all includes of this manifest
     */
    const std::vector<std::shared_ptr<manifest::Include>> &get_includes() const; //<swig_out/>

    //! Equal to comparison operator
    bool operator==(const Manifest &other) const;

    //! Not equal to comparison operator
    bool operator!=(const Manifest &other) const;

private:
    //!< \cond DOXY_IMPL
    manifest::Type m_type = manifest::Type::NOT_SET;                            //!< The type of repository
    manifest::Kind m_kind = manifest::Kind::NOT_SET;                            //!< The kind of repository
    manifest::Format m_format = manifest::Format::NOT_SET;                      //!< The format of repository
    std::vector<std::shared_ptr<manifest::Location>> m_locations;               //!< All the locations
    std::map<std::string, std::shared_ptr<manifest::Location>> m_map_locations; //!< The map of all locations by name
    std::map<std::string, std::shared_ptr<manifest::Location>>
        m_map_locations_by_path;                            //!< The map of all locations by path
    std::shared_ptr<manifest::Location> m_default_location; //!< The default location
    manifest::Groups m_groups;                              //!< The groups defiend in the manifest
    std::string m_default_location_str;                     //!< The name of the default location
    std::string m_default_revision = "master";              //!< The default revision
    int m_default_job_count = 1;                            //!< The default number of concurrent jobs
    std::vector<std::shared_ptr<manifest::Include>> m_includes;
    //!< \endcond
};

ESYSREPO_API std::ostream &operator<<(std::ostream &os, const Manifest &manifest); //<swig_out/>

} // namespace repo

} // namespace esys
