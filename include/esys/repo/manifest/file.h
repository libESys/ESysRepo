/*!
 * \file esys/repo/manifest/file.h
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
#include "esys/repo/manifest.h"

#include <string>
#include <memory>

namespace esys
{

namespace repo
{

namespace manifest
{

/*! \class File esys/repo/manifest/file.h "esys/repo/manifest/file.h"
 * \brief Base class for all ESysRepo manifest file format
 */
class ESYSREPO_API File
{
public:
    //! Default constructor
    File();

    //! Destructor
    virtual ~File();

    //! Set the manifest data
    /*!
     * \param[in] manifest the manifest data
     */
    void set_manifest(std::shared_ptr<Manifest> manifest);

    //! Get the manifest data
    /*!
     * \return the manifest data
     */
    std::shared_ptr<Manifest> get_manifest();

    //! Get the manifest data
    /*!
     * \return the manifest data
     */
    const std::shared_ptr<Manifest> get_manifest() const;

    //! Read the ESysRepo manifest
    /*!
     * \param[in] path the path of the ESysRepo manifest
     * \return 0 if successful, < 0 otherwise
     */
    virtual int read(const std::string &path) = 0;

    //! Write this ESysRepo manifest
    /*!
     * \param[in] path the path of the ESysRepo manifest
     * \return 0 if successful, < 0 otherwise
     */
    virtual int write(const std::string &path) = 0;

protected:
    //!< \cond DOXY_IMPL
    std::shared_ptr<Manifest> m_manifest; //!< The manifest data
    //!< \endcond
};

} // namespace manifest

} // namespace repo

} // namespace esys
