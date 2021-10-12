/*!
 * \file esys/repo/configfile.h
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
#include "esys/repo/config.h"

#include <string>
#include <memory>

namespace esys
{

namespace repo
{

class ESYSREPO_API ConfigFileImpl;

/*! \class ConfigFile esys/repo/configfile.h "esys/repo/configfile.h"
 * \brief Read and write the ESysRepo configuration file
 */
class ESYSREPO_API ConfigFile
{
public:
    //! Default constructor
    ConfigFile();

    //! Destructor
    virtual ~ConfigFile();

    //! Set the path of the config file
    /*!
     * \param[in] path the path of the config file
     */
    void set_path(const std::string &path);

    //! Get the path of the config file
    /*!
     * \return the path of the config file
     */
    const std::string &get_path() const;

    //! Set the configuration data of the config file
    /*!
     * \param[in] config the configuration data of the config file
     */
    void set_config(std::shared_ptr<Config> config);

    //! Get the configuration data of the config file
    /*!
     * \return the configuration data of the config file
     */
    std::shared_ptr<Config> get_config();

    //! Get the configuration data of the config file
    /*!
     * \return the configuration data of the config file
     */
    const std::shared_ptr<Config> get_config() const;

    //! Open and read a config file
    /*!
     * \param[in] path the path of the config file to open and read
     */
    int open(const std::string &path = "");

    //! Write a config file
    /*!
     * \param[in] path the path of the config file to write
     */
    int write(const std::string &path = "");

    //! Get the PIMPL
    /*!
     * \return the PIMPL
     */
    ConfigFileImpl *get_impl();

    //! Get the PIMPL
    /*!
     * \return the PIMPL
     */
    const ConfigFileImpl *get_impl() const;

private:
    //!< \cond DOXY_IMPL
    std::unique_ptr<ConfigFileImpl> m_impl; //!< the PIMPL
    std::shared_ptr<Config> m_config;       //!< The configuration data
    std::string m_path;                     //!< The path of the config file
    //!< \endcond
};

} // namespace repo

} // namespace esys
