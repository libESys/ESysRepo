/*!
 * \file esys/repo/manifest/syncrepo.h
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
#include "esys/repo/gitbase.h"
#include "esys/repo/manifest/repository.h"
#include "esys/repo/manifest/taskbase.h"
#include "esys/repo/githelper.h"

#include <esys/log/user.h>

#include <memory>
#include <mutex>

namespace esys
{

namespace repo
{

namespace manifest
{

/*! \class SyncRepo esys/repo/manifest/syncrepo.h "esys/repo/manifest/syncrepo.h"
 * \brief Sync one repos found in a manifest
 */
class ESYSREPO_API SyncRepo : public TaskBase, public log::User
{
public:
    //! Default constructor
    SyncRepo();

    //! Destructor
    ~SyncRepo() override;

    int run() override;

    //! Process one repository
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    virtual int process_repo();

    //! Clone one new repository
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    virtual int clone();

    //! Fetch and/or update one existing repository
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    virtual int fetch_update();

    //! Set the log level
    /*!
     * \param[in] log_level the log level
     */
    void set_log_level(log::Level log_level);

    //! Get the log level
    /*!
     * \return the log level
     */
    log::Level get_log_level();

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

    void set_display_repo_idx(bool display_repo_idx);
    bool get_display_repo_idx() const;

    std::string get_repo_url();

    void set_branch(const std::string &branch);
    const std::string &get_branch() const;

    void set_alt_address(bool alt_address);
    bool get_alt_address() const;

    void set_force(bool force);
    bool get_force() const;

    static int normal_sync(GitHelper &git_helper);
    int branch_sync(GitHelper &git_helper);

protected:
    //!< \cond DOXY_IMPL
    static bool has_branch(GitHelper &git_helper, const std::string &branch);
    std::string get_checkout_revision(GitHelper &git_helper);
    std::shared_ptr<GitHelper> new_git_helper();

private:
    std::shared_ptr<ConfigFolder> m_config_folder; //!< The config folder
    std::shared_ptr<GitBase> m_git;                //!< The git instance
    std::shared_ptr<manifest::Repository> m_repo;  //!< The git repository to process
    log::Level m_log_level = log::Level::INFO;     //!< The log level
    std::size_t m_repo_idx = 0;                    //!< The repo index
    bool m_display_repo_idx = true;                //!< Tells if the repo idx should be displayed
    std::string m_branch;                          //!< The branch to checkout if existing
    bool m_force = false;                          //!< Force the operation
    bool m_alt_address = false;                    //!< Use alternative address of the git repo

    //!< \endcond
};

} // namespace manifest

} // namespace repo

} // namespace esys
