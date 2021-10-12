/*!
 * \file esys/repo/manifest/xmlfile.h
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
#include "esys/repo/manifest/base.h"

#include <memory>

namespace esys
{

namespace repo
{

namespace manifest
{

class ESYSREPO_API XMLFileImpl;

/*! \class XMLFile esys/repo/manifest/xmlfile.h "esys/repo/manifest/xmlfile.h"
 * \brief Read and write the ESysRepo manifest in XML format
 */
class ESYSREPO_API XMLFile : public Base
{
public:
    //! Default constructor
    XMLFile();

    //! Destructor
    ~XMLFile() override;

    //! Read a XML ESysRepo manifest file
    /*!
     * \param[in] path the path of the XML ESysRepo manifest file to read
     * \return 0 if successful, < 0 otherwise
     */
    int read(const std::string &path) override;

    //! Write a XML ESysRepo manifest file
    /*!
     * \param[in] path the path of the XML ESysRepo manifest file to write
     * \return 0 if successful, < 0 otherwise
     */
    int write(const std::string &path) override;

    //! Write a XML ESysRepo manifest to a stream
    /*!
     * \param[in] os the stream
     * \return 0 if successful, < 0 otherwise
     */
    int write(std::ostream &os) override;

    //! Get the PIMPL
    /*!
     * \return the PIMPL
     */
    XMLFileImpl *get_impl();

    //! Get the PIMPL
    /*!
     * \return the PIMPL
     */
    const XMLFileImpl *get_impl() const;

private:
    //!< \cond DOXY_IMPL
    std::unique_ptr<XMLFileImpl> m_impl; //!< The PIMPL
    //!< \endcond
};

} // namespace manifest

} // namespace repo

} // namespace esys
