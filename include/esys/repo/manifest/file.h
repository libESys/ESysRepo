/*!
 * \file esys/repo/manifest/file.h
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
    void set_data(std::shared_ptr<Manifest> manifest);

    //! Get the manifest data
    /*!
     * \return the manifest data
     */
    std::shared_ptr<Manifest> get_data();

    //! Get the manifest data
    /*!
     * \return the manifest data
     */
    const std::shared_ptr<Manifest> get_data() const;

    //! Read the manifest
    /*!
     * \param[in] path the path of the manifest
     * \return 0 if successful, < 0 otherwise
     */
    virtual int read(const std::string &path) = 0;

    //! Write this manifest to a file
    /*!
     * \param[in] path the path of the ESysRepo manifest
     * \return 0 if successful, < 0 otherwise
     */
    virtual int write(const std::string &path) = 0;

    //! Write the manifest to a stream
    /*!
     * \param[in] os the stream
     */
    virtual int write(std::ostream &os) = 0;

protected:
    //!< \cond DOXY_IMPL
    std::shared_ptr<Manifest> m_data; //!< The abstract data of a manifest
    //!< \endcond
};

} // namespace manifest

} // namespace repo

} // namespace esys
