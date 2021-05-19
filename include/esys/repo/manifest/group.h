/*!
 * \file esys/repo/manifest/group.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2021 Michel Gillet
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

namespace esys
{

namespace repo
{

namespace manifest
{

class ESYSREPO_API Repository;

/*! \class Group esys/repo/manifest/group.h "esys/repo/manifest/group.h"
 * \brief Data for a group in a ESysRepo manifest
 */
class ESYSREPO_API Group : public std::enable_shared_from_this<Group>
{
public:
    //! Default constructor
    Group();

    //! Constructor
    Group(const std::string &name);

    //! Destructor
    virtual ~Group();

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
    const std::vector<std::shared_ptr<Repository>> &get_repos() const;

    std::shared_ptr<Repository> find_repo_by_path(const std::string &path);
    std::shared_ptr<Repository> find_repo_by_name(const std::string &name);

protected:
    //!< \cond DOXY_IMPL
    std::string m_name;                               //!< The name of this location
    std::vector<std::shared_ptr<Repository>> m_repos; //!< All repositories of this location
    std::map<std::string, std::shared_ptr<Repository>> m_map_repos_by_path;
    std::map<std::string, std::shared_ptr<Repository>> m_map_repos_by_name;
    //!< \endcond
};

} // namespace manifest

} // namespace repo

} // namespace esys
