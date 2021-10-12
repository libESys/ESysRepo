/*!
 * \file esys/repo/manifestfilebase.h
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

#include <string>
#include <ostream>
#include <memory>

//<swig_inc/>

namespace esys
{

namespace repo
{

/*! \class ManifestFileBase esys/repo/manifestfilebase.h "esys/repo/manifestfilebase.h"
 * \brief
 */
class ESYSREPO_API ManifestFileBase
{
public:
    //! Default contructor
    ManifestFileBase();

    //! Destructor
    virtual ~ManifestFileBase();

    //! Read a manifest
    /*!
     * \param[in] filename the filename of the manifest to read
     */
    virtual int read(const std::string &filename) = 0;

    //! Write the manifest to a file
    /*!
     * \param[in] filename the filename
     */
    virtual int write(const std::string &filename) = 0;

    //! Write the manifest to a stream
    /*!
     * \param[in] os the stream
     */
    virtual int write(std::ostream &os) = 0;

    //! Set the abstract data of a manifest
    /*!
     * \param[in] data the abstract data of a manifest
     */
    virtual void set_data(std::shared_ptr<repo::Manifest> data);

    //! Get the abstract data of a manifest
    /*!
     * \return the abstract data of a manifest
     */
    virtual std::shared_ptr<repo::Manifest> get_data();

    //! Get the abstract data of a manifest
    /*!
     * \return the abstract data of a manifest
     */
    virtual const std::shared_ptr<repo::Manifest> get_data() const;

private:
    //!< \cond DOXY_IMPL
    std::shared_ptr<repo::Manifest> m_data; //!< The abstract data of a manifest
    //!< \endcond
};

} // namespace repo

} // namespace esys
