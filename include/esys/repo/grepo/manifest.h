/*!
 * \file esys/repo/grepo/manifest.h
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
#include "esys/repo/manifest/file.h"

#include <memory>

namespace esys
{

namespace repo
{

namespace grepo
{

class ESYSREPO_API ManifestImpl;

/*! \class Manifest esys/repo/grepo/manifest.h "esys/repo/grepo/manifest.h"
 * \brief Hold information about a google repo tool manifest
 */
class ESYSREPO_API Manifest : public manifest::File
{
public:
    //! Default constructor
    Manifest();

    //! Destructor
    virtual ~Manifest();

    int read(const std::string &filename) override;
    int write(const std::string &filename) override;
    int write(std::ostream &os) override;

    //! Equal to comparison operator
    bool operator==(const Manifest &other) const;

    //! Not equal to comparison operator
    bool operator!=(const Manifest &other) const;

    //! Get the PIMPL
    /*!
     * \return the PIMPL
     */
    ManifestImpl *get_impl();

protected:
    //!< \cond DOXY_IMPL
    std::unique_ptr<ManifestImpl> m_impl;   //!< The PIMPL
    //!< \endcond
};

ESYSREPO_API std::ostream &operator<<(std::ostream &os, const Manifest &manifest);

} // namespace grepo

} // namespace repo

} // namespace esys
