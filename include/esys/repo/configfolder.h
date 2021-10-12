/*!
 * \file esys/repo/configfolder.h
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
#include "esys/repo/configfile.h"

#include <esys/log/user.h>

#include <string>
#include <vector>
#include <memory>

namespace esys
{

namespace repo
{

/*! \class ConfigFolder esys/repo/configfolder.h "esys/repo/configfolder.h"
 * \brief Handle the folder used by ESysRepo to store config information
 */
class ESYSREPO_API ConfigFolder : public log::User
{
public:
    //! Default constructor
    ConfigFolder();

    //! Destructor
    ~ConfigFolder() override;

    //! Set the parent path of the ConfigFolder
    /*!
     * \param[in] path the parent path of the ConfigFolder
     */
    void set_workspace_path(const std::string &path);

    //! Get the parent path of the ConfigFolder
    /*!
     * \return the parent path of the ConfigFolder
     */
    const std::string &get_workspace_path() const;

    //! Create a new ConfigFolder
    /*!
     * \param[in] parent_path the parent path of the ConfigFolder
     */
    int create(const std::string &parent_path = "");

    //! Open a ConfigFolder
    /*!
     * \param[in] parent_path the parent path of the ConfigFolder
     */
    int open(const std::string &parent_path = "");

    //! Write and update a ConfigFolder
    /*!
     * \param[in] parent_path the parent path of the ConfigFolder
     */
    int write(const std::string &parent_path = "");

    //! Get the path of the ConfigFolder
    /*!
     * \return the path of the ConfigFolder
     */
    const std::string &get_path() const;

    //! Get the temporary path of the ConfigFolder
    /*!
     * \return the parent path of the ConfigFolder
     */
    const std::string &get_temp_path() const;

    //! Get the path of the ConfigFile in the config folder
    /*!
     * \return the path of the ConfigFile in the config folder
     */
    const std::string &get_config_file_path() const;

    //! Get the absolute path of the git repo holding the manifest
    /*!
     * \return the absolute path of the git repo holding the manifest
     */
    std::string get_manifest_repo_path() const;

    //! Get the path to the manifest file but relative to the git repo where it is located
    /*!
     * \return the reltive path to the manifest file
     */
    std::string get_manifest_rel_file_name() const;

    //! Get the ESysRepo configuration stored in the git repo
    /*!
     * \return the ESysRepo configuration stored in the git repo
     */
    std::shared_ptr<Config> get_config();

    //! Get the ESysRepo configuration stored in the git repo
    /*!
     * \return the ESysRepo configuration stored in the git repo
     */
    std::shared_ptr<Config> get_config() const;

    //! Set the ESysRepo configuration stored in the git repo
    /*!
     * \param[in] config the ESysRepo configuration stored in the git repo
     */
    void set_config(std::shared_ptr<Config> config);

    //! Get the ESysRepo configuration stored in the git repo and create one if not set
    /*!
     * \return the ESysRepo configuration stored in the git repo
     */
    std::shared_ptr<Config> get_or_new_config();

    //! Write the content of the Config instance to the config file
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    int write_config_file();

    //! Populate all paths based on the parent path
    void populate_all_pathes();

    //! Tells if the path is the ESysRepo folder
    /*!
     * \param[in] path the path to check
     * \return true if the path is the ESysRepo folder, false otherwise
     */
    static bool is_config_folder(const std::string &path);

private:
    //!< \cond DOXY_IMPL
    std::string m_parent_path;                 //!< The parent path
    std::string m_path;                        //!< The actual path of the ESysRepo config folder
    std::string m_temp_path;                   //!< The path of the temporary folder
    std::string m_config_file_path;            //!< The path of the configuration file
    std::shared_ptr<Config> m_config;          //!< The configuration data
    std::shared_ptr<ConfigFile> m_config_file; //!< The configuration file
    //!< \endcond
};

} // namespace repo

} // namespace esys
