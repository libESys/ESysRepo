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

/*! \class Repository esys/repo/manifest/repository.h "esys/repo/manifest/repository.h"
 * \brief Data for a repository in a ESysRepo manifest
 */
class ESYSREPO_API Repository
{
public:
    //! Default constructor
    Repository();

    //! Constructor
    Repository(const std::string &name, const std::string &path);

    //! Destrutor
    virtual ~Repository();

    //! Set the name of the repository
    /*!
     * \param[in] name the name of the repository
     */
    void set_name(const std::string &name);

    //! Get the name of the repository
    /*!
     * \return the name of the repository
     */
    const std::string &get_name() const;

    //! Set the path of the repository
    /*!
     * \param[in] path the path of the repository
     */
    void set_path(const std::string &path);

    //! Get the path of the repository
    /*!
     * \return the path of the repository
     */
    const std::string &get_path() const;

    //! Set the revision of the repository
    /*!
     * \param[in] revision the revision of the repository
     */
    void set_revision(const std::string &revision);

    //! Get the revision of the repository
    /*!
     * \return the revision of the repository
     */
    const std::string get_revision() const;

    //! Set the name of the location
    /*!
     * \param[in] location_str the name of the location
     */
    void set_location(const std::string &location_str);

    //! Get the name of the location
    /*!
     * \return the name of the location
     */
    const std::string &get_location_str() const;

    //! Set the location
    /*!
     * \param[in] location the location
     */
    void set_location(Location *location);

    //! Get the location
    /*!
     * \return the location
     */
    Location *get_location() const;

protected:
    //!< \cond DOXY_IMPL
    std::string m_name;             //!< The name of the repository
    std::string m_path;             //!< The path of the repository
    std::string m_revision;         //!< The revision of the repository
    Location *m_location = nullptr; //!< The location of the repository
    std::string m_location_str;     //!< The name of location of the repository
    //!< \endcond
};

} // namespace manifest

} // namespace repo

} // namespace esys