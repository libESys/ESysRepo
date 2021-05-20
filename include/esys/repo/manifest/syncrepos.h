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
#include "esys/repo/manifest/syncrepo.h"
#include "esys/repo/manifest/runtasks.h"
#include "esys/repo/gitbase.h"

#include <esys/log/user.h>

#include <memory>
#include <string>
#include <vector>

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

    //! Get the git instance to use, create one if needed
    /*!
     * \retrun the git instance
     */
    std::shared_ptr<GitBase> get_git_or_new();

    //! Set the git generator to use
    /*!
     * \param[in] git_generator the git generator to use
     */
    void set_git_generator(GitBase::GeneratorType git_generator);

    //! Get the git generator to use
    /*!
     * \return the git generator to use
     */
    GitBase::GeneratorType get_git_generator();

    //! Create a new git instance
    /*!
     * \return a new git instance
     */
    std::shared_ptr<GitBase> new_git();

    //! Do the work
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    virtual int run();

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

    bool is_repo_to_be_synced(std::shared_ptr<manifest::Repository> repo) const;
    void set_folders_to_sync(std::vector<std::string> folders_to_sync);
    const std::vector<std::string> &get_folders_to_sync() const;

    void set_job_count(int job_count);
    int get_job_count() const;

    void set_branch(const std::string &branch);
    const std::string &get_branch() const;

    RunTasks &get_run_tasks();
    const RunTasks &get_run_tasks() const;

    static bool globly_match(const std::string &text, const std::string &glob);

protected:
    //!< \cond DOXY_IMPL
    std::shared_ptr<Manifest> m_manifest;              //!< The manifest
    std::shared_ptr<ConfigFolder> m_config_folder;     //!< The config folder
    GitBase::GeneratorType m_git_generator = nullptr;  //!< Git generator
    std::shared_ptr<GitBase> m_git;                    //!< The git instance
    log::Level m_log_level = log::Level::INFO;         //!< The log level
    std::size_t m_repo_idx = 0;                        //!< The repo index
    RunTasks m_run_tasks;                              //!< Mamange a set of threads to run a list of tasks
    std::vector<std::string> m_folders_to_sync;        //!< The list of folders to sync
    std::map<std::string, bool> m_map_folders_to_sync; //!< The map of folders to sync
    std::string m_branch;                              //!< The branch to checkout if found
    //!< \endcond
};

} // namespace manifest

} // namespace repo

} // namespace esys
