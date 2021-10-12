/*!
 * \file esys/repo/manifest/loader.h
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
#include "esys/repo/manifest/loaderbase.h"

#include <memory>

namespace esys
{

namespace repo
{

namespace manifest
{

/*! \class Loader esys/repo/manifest/loader.h "esys/repo/manifest/loader.h"
 * \brief Class loading all known manifest format from a ESysRepo folder
 */
class ESYSREPO_API Loader : public LoaderBase
{
public:
    //! Default constructor
    Loader();

    //! Destructor
    ~Loader() override;

    int run() override;

    //! Set the actual loader to use
    /*!
     * \param[in] loader the actual loader to use
     */
    void set_loader(std::shared_ptr<LoaderBase> loader);

    //! Get the actual loader to use
    /*!
     * \return the actual loader to use
     */
    std::shared_ptr<LoaderBase> get_loader();

    //! Get the actual loader to use
    /*!
     * \return the actual loader to use
     */
    const std::shared_ptr<LoaderBase> get_loader() const;

private:
    //!< \cond DOXY_IMPL
    std::shared_ptr<LoaderBase> m_loader;
    //!< \endcond
};

} // namespace manifest

} // namespace repo

} // namespace esys
