/*!
 * \file esys/repo/manifest/syncrepos.h
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
#include "esys/repo/configfolder.h"
#include "esys/repo/manifest/repository.h"
#include "esys/repo/gitbase.h"

#include <esys/log/user.h>

#include <memory>

namespace esys
{

namespace repo
{

namespace manifest
{

/*! \class SyncRepos esys/repo/manifest/syncrepos.h "esys/repo/manifest/syncrepos.h"
 * \brief Sync all repos found in a manifest
 */
class ESYSREPO_API SyncRepos : public log::User
{
public:
    //! Default constructor
    SyncRepos();

    //! Destructor
    virtual ~SyncRepos();

    //! Set the manifest
    /*!
     * \param[in] manifest the manifest
     */
    void set_manifest(std::shared_ptr<Manifest> manifest);

    //! Get the manifest
    /*!
     * \return the manifest
     */
    std::shared_ptr<Manifest> get_manifest();

    //! Get the manifest
    /*!
     * \return the manifest
     */
    const std::shared_ptr<Manifest> get_manifest() const;

    //! Set the config folder
    /*!
     * \param[in] config_folder the config folder
     */
    void set_config_folder(std::shared_ptr<ConfigFolder> config_folder);

    //! Get the config folder
    /*!
     * \return the config folder
     */
    std::shared_ptr<ConfigFolder> get_config_folder();

    //! Get the config folder
    /*!
     * \return the config folder
     */
    const std::shared_ptr<ConfigFolder> get_config_folder() const;

    //! Set the git instance to use
    /*!
     * \param[in] git the git instance
     */
    void set_git(std::shared_ptr<GitBase> git);

    //! Get the git instance to use
    /*!
     * \retrun the git instance
     */
    std::shared_ptr<GitBase> get_git();

    //! Get the git instance to use
    /*!
     * \retrun the git instance
     */
    const std::shared_ptr<GitBase> get_git() const;

    //! Do the work
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    virtual int run();

    //! Process one repository
    /*!
     * \param[in] repository the repository to process
     * \param[in] repo_idx the repository index
     * \return 0 if successful, < 0 otherwise
    */
    virtual int process_repo(std::shared_ptr<manifest::Repository> repository, std::size_t repo_idx);

    //! Clone one new repository
    /*!
     * \param[in] repository the repository to process
     * \param[in] repo_idx the repository index
     * \return 0 if successful, < 0 otherwise
     */
    virtual int clone(std::shared_ptr<manifest::Repository> repository, std::size_t repo_idx);

    //! Fetch and/or update one existing repository
    /*!
     * \param[in] repository the repository to process
     * \param[in] repo_idx the repository index
     * \return 0 if successful, < 0 otherwise
     */
    virtual int fetch_update(std::shared_ptr<manifest::Repository> repository, std::size_t repo_idx);

    //! Set the log level
    /*!
     * \param[in] log_level the log level
     */
    void set_log_level(log::Level log_level);

    //! Get the log level
    /*!
     * \return the log level
     */
    log::Level get_log_level() const;

    //! Set the repo index
    /*!
     * \param[in] repo_idx the repo index
     */
    void set_repo_idx(std::size_t repo_idx);

    //! Get the repo index
    /*!
     * \return the repo index
     */
    std::size_t get_repo_idx() const;

    //! Get the repo index
    /*!
     * \return the repo index
     */
    std::size_t &get_repo_idx();

protected:
    //!< \cond DOXY_IMPL
    std::shared_ptr<Manifest> m_manifest;          //!< The manifest
    std::shared_ptr<ConfigFolder> m_config_folder; //!< The config folder
    std::shared_ptr<GitBase> m_git;                //!< The git instance
    log::Level m_log_level = log::Level::INFO;     //!< The log level
    std::size_t m_repo_idx = 0;                    //!< The repo index
    //!< \endcond
};

} // namespace manifest

} // namespace repo

} // namespace esys
