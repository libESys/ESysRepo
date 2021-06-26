/*!
 * \file esys/repo/manifest/file.h
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
#include "esys/repo/manifest.h"
#include "esys/repo/manifest/filebase.h"

#include <memory>

namespace esys
{

namespace repo
{

namespace manifest
{

/*! \class File esys/repo/manifest/file.h "esys/repo/manifest/file.h"
 * \brief Read and write the ESysRepo manifest file
 */
class ESYSREPO_API File : public FileBase
{
public:
    //! Default constructor
    File();

    //! Destructor
    virtual ~File();

    //! Read a ESysRepo manifest file
    /*!
     * \param[in] path the path of the ESysRepo manifest file to read
     * \return 0 if successful, < 0 otherwise
     */
    int read(const std::string &path) override;

    //! Write a ESysRepo manifest file
    /*!
     * \param[in] path the path of the ESysRepo manifest file to write
     * \return 0 if successful, < 0 otherwise
     */
    int write(const std::string &path) override;

    //! Write a ESysRepo manifest to a stream
    /*!
     * \param[in] os the stream
     * \return 0 if successful, < 0 otherwise
     */
    int write(std::ostream &os) override;

    //! Get the PIMPL
    /*!
     * \return the PIMPL
     */
    FileBase *get_impl();

    //! Get the PIMPL
    /*!
     * \return the PIMPL
     */
    const FileBase *get_impl() const;

protected:
    //!< \cond DOXY_IMPL
    std::unique_ptr<FileBase> m_impl; //!< The PIMPL
    //!< \endcond
};

} // namespace manifest

} // namespace repo

} // namespace esys
