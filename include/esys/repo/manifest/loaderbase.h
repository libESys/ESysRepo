/*!
 * \file esys/repo/manifest/loaderbase.h
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
#include "esys/repo/config.h"
#include "esys/repo/configfolder.h"

#include <esys/log/user.h>

#include <memory>

namespace esys
{

namespace repo
{

namespace manifest
{

/*! \class LoaderBase esys/repo/manifest/loaderbase.h "esys/repo/manifest/loaderbase.h"
 * \brief Base class for all manifest loaders
 */
class ESYSREPO_API LoaderBase : public log::User
{
public:
    //! Default constructor
    LoaderBase();

    //! Destructor
    ~LoaderBase() override;

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

    //! Set the ESysRepo configuration
    /*!
     * \param[in] config the ESysRepo configuration
     */
    void set_config(std::shared_ptr<Config> config);

    //! Get the ESysRepo configuration
    /*!
     * \return the ESysRepo configuration
     */
    std::shared_ptr<Config> get_config();

    //! Get the ESysRepo configuration
    /*!
     * \return the ESysRepo configuration
     */
    const std::shared_ptr<Config> get_config() const;

    //! Set the ESysRepo configuration folder
    /*!
     * \param[in] config the ESysRepo configuration folder
     */
    void set_config_folder(std::shared_ptr<ConfigFolder> config_folder);

    //! Get the ESysRepo configuration folder
    /*!
     * \return the ESysRepo configuration folder
     */
    std::shared_ptr<ConfigFolder> get_config_folder();

    //! Get the ESysRepo configuration folder
    /*!
     * \return the ESysRepo configuration folder
     */
    const std::shared_ptr<ConfigFolder> get_config_folder() const;

    //! Load the manifest
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    virtual int run() = 0;

private:
    //!< \cond DOXY_IMPL
    std::shared_ptr<Manifest> m_manifest;          //!< The manifest data
    std::shared_ptr<Config> m_config;              //!< The ESysRepo configuration
    std::shared_ptr<ConfigFolder> m_config_folder; //!< The ESysRepo configuration folder
    //!< \endcond
};

} // namespace manifest

} // namespace repo

} // namespace esys
