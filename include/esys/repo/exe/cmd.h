/*!
 * \file esys/repo/exe/cmd.h
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
#include "esys/repo/gitbase.h"
#include "esys/repo/manifest.h"
#include "esys/repo/manifest/type.h"
#include "esys/repo/manifest/loader.h"
#include "esys/repo/configfolder.h"

#include <esys/log/user.h>

#include <memory>

namespace esys
{

namespace repo
{

namespace exe
{

/*! \class Cmd esys/repo/exe/cmd.h "esys/repo/exe/cmd.h"
 * \brief Base class of all commands of the ESysRepo tool
 */
class ESYSREPO_API Cmd : public log::User
{
public:
    //! Default constructor
    Cmd();

    //! Destructor
    virtual ~Cmd();

    //! Set the manifest
    /*!
     * \param[in] manifest the manifest
     */
    void set_manifest(std::shared_ptr<Manifest> manifest);

    //! Get the manifest
    /*!
     * \retrun the manifest
     */
    std::shared_ptr<Manifest> get_manifest();

    //! Get the manifest
    /*!
     * \retrun the manifest
     */
    const std::shared_ptr<Manifest> get_manifest() const;

    //! Set the git instance
    /*!
     * \param[in] git the git instance
     */
    void set_git(std::shared_ptr<GitBase> git);

    //! Get the git instance
    /*!
     * \return the git instance
     */
    std::shared_ptr<GitBase> get_git();

    //! Get the git instance
    /*!
     * \return the git instance
     */
    const std::shared_ptr<GitBase> get_git() const;

    //! Set the parent path
    /*!
     * \param[in] parent_path the parent path
     */
    void set_parent_path(const std::string &parent_path);

    //! Get the parent path
    /*!
     * \return the parent path
     */
    const std::string &get_parent_path() const;

    //! Set the config folder
    /*!
     * \param[in] config_folder the config folder
     */
    void set_config_folder(std::shared_ptr<ConfigFolder> config_folder);

    //! Get the config folder
    /*!
     * \retrun the config folder
     */
    std::shared_ptr<ConfigFolder> get_config_folder();

    //! Get the config folder
    /*!
     * \retrun the config folder
     */
    const std::shared_ptr<ConfigFolder> get_config_folder() const;

    //! Set the manifest loader to use
    /*!
     * \param[in] loader the manifest loader to use
     */
    void set_loader(std::shared_ptr<manifest::Loader> loader);

    //! Get the manifest loader to use
    /*!
     * \return the manifest loader to use
     */
    std::shared_ptr<manifest::Loader> get_loader();

    //! Get the manifest loader to use
    /*!
     * \return the manifest loader to use
     */
    const std::shared_ptr<manifest::Loader> get_loader() const;

    //! Find the parent path if any given a child path
    /*!
     * \param[in] path the child path is provided, otherwise the current path will be used
     * \return the parent path if found, empty string otherwise
     */
    static std::string find_parent_path(const std::string &path = "");

    //! Do the work
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    virtual int run() = 0;

    //! Set if debug information are printed or not
    /*!
     * \param[in] debug if true debug information are printed
     */
    void set_debug(bool debug = true);

    //! Get if debug information are printed or not
    /*!
     * \return if true debug information are printed
     */
    bool get_debug() const;

    //! Set folder in use and find the parent path for it
    /*!
     * \param[in] folder the folder
     */
    int set_folder(const std::string &folder);

protected:
    //!< \cond DOXY_IMPL

    //! Helper function to open the ESysRep config folder and file
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    int open_esysrepo_folder();
    
    //! Helper function to load the manifest
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    int load_manifest();

    std::shared_ptr<Manifest> m_manifest;          //!< The manifest to use
    std::shared_ptr<GitBase> m_git;                //!< The git instance to use
    bool m_debug = false;                          //!< If true debug information is printed
    std::string m_folder;                          //!< The current folder
    std::string m_parent_path;                     //!< The parent path
    std::shared_ptr<ConfigFolder> m_config_folder; //!< The config folder
    std::shared_ptr<manifest::Loader> m_loader;    //!< The manifest loader
    //!< \endcond
};

} // namespace exe

} // namespace repo

} // namespace esys