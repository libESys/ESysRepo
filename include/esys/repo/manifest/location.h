/*!
 * \file esys/repo/manifest/location.h
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

#include <string>
#include <vector>
#include <memory>
#include <map>

//<swig_inc/>

//<swig>%shared_ptr(esys::repo::manifest::Location);</swig>
//<swig>%template(VecSPtrLocation) std::vector<std::shared_ptr<esys::repo::manifest::Location>>;</swig>

namespace esys::repo::manifest
{

class ESYSREPO_API Repository;

/*! \class Location esys/repo/manifest/location.h "esys/repo/manifest/location.h"
 * \brief Data for a location in a ESysRepo manifest
 */
class ESYSREPO_API Location : public std::enable_shared_from_this<Location>
{
public:
    //! Default constructor
    Location();

    //! Constructor
    Location(const std::string &name, const std::string &address);

    //! Destructor
    virtual ~Location();

    //! Set the name of the location
    /*!
     * \param[in] name the name of the location
     */
    void set_name(const std::string &name);

    //! Get the name of the location
    /*!
     * \return the name of the location
     */
    const std::string &get_name() const;

    //! Set the address of the location
    /*!
     * \param[in] address the address of the location
     */
    void set_address(const std::string &address);

    //! Get the address of the location
    /*!
     * \return the address of the location
     */
    const std::string &get_address() const;

    bool is_address_ssh() const;

    //! Set the address of the location
    /*!
     * \param[in] address the alternative address of the location
     */
    void set_alt_address(const std::string &alt_address);

    //! Get the alternative address of the location
    /*!
     * \return the alternative address of the location
     */
    const std::string &get_alt_address() const;

    bool is_alt_address_ssh() const;

    //! Add a repository to this location
    /*!
     * \param[in] name the name of the repository
     * \param[in] path the path of the repository
     */
    std::shared_ptr<Repository> add_repo(const std::string &name, const std::string &path);

    //! Add a repository to this location
    /*!
     * \param[in] repo the repository
     */
    void add_repo(std::shared_ptr<Repository> repo);

    //! Get all repositories of this location
    /*!
     * \return all repositories of this location
     */
    std::vector<std::shared_ptr<Repository>> &get_repos();

    //! Get all repositories of this location
    /*!
     * \return all repositories of this location
     */
    const std::vector<std::shared_ptr<Repository>> &get_repos() const; //<swig_out/>

    std::shared_ptr<Repository> find_repo_by_path(const std::string &path);
    std::shared_ptr<Repository> find_repo_by_name(const std::string &name);
    std::string find_repo_path_by_url(const std::string &url);

    std::shared_ptr<manifest::Repository> find_repo_by_url(const std::string &url);

    //! Equal to comparison operator
    bool operator==(const Location &location) const;

    //! Not equal to comparison operator
    bool operator!=(const Location &location) const;

    Location(const Location &) = delete;
    Location(Location &&) = delete;

    static void remove_dot_git(std::string &text);

private:
    //!< \cond DOXY_IMPL
    std::string m_name;                               //!< The name of this location
    std::string m_address;                            //!< The address of this location
    std::string m_alt_address;                        //!< The alternative address of this location
    std::vector<std::shared_ptr<Repository>> m_repos; //!< All repositories of this location
    std::map<std::string, std::shared_ptr<Repository>> m_map_repos_by_path;
    std::map<std::string, std::shared_ptr<Repository>> m_map_repos_by_name;
    //!< \endcond
};

ESYSREPO_API std::ostream &operator<<(std::ostream &os, const Location &location);

} // namespace esys::repo::manifest
