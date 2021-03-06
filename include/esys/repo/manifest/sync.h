/*!
 * \file esys/repo/manifest/sync.h
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
#include "esys/repo/configfolder.h"
#include "esys/repo/gitbase.h"

#include <esys/log/user.h>

#include <memory>

namespace esys
{

namespace repo
{

namespace manifest
{

/*! \class Sync esys/repo/manifest/sync.h "esys/repo/manifest/sync.h"
 * \brief Sync the manifest
 */
class ESYSREPO_API Sync : public log::User
{
public:
    enum
    {
        NOT_IMPLEMENTED = -127,
        GIT_IS_NULL = -1,
        GIT_IS_NOT_OPENED = -2,
        GIT_OPEN_FAILED = -3,
        GIT_IS_DIRTY_FAILED = -4,
        GIT_GET_STATUS_FAILED = -5,
        CONFIG_FOLDER_IS_NULL = -6,
        CONFIG_IS_NULL = -7,
        GIT_FETCH_FAILED = -8,
        GIT_GET_BRANCHES_FAILED = -9,
        GIT_GET_HEAD_FAILED = -10,
        GIT_MERGE_ANALYSIS_FAILED = -11,
        GIT_CAN_NOT_BE_FAST_FORWARDED = -12,
        GIT_MORE_THAN_ONE_COMMIT = -13,
        GIT_FAST_FORWARD_FAILED = -14,
    };

    //! Default constructor
    Sync();

    //! Destructor
    ~Sync() override;

    void set_branch(const std::string &branch);
    const std::string &get_branch() const;

    void set_force(bool force = true);
    bool get_force() const;

    Result run();

    Result normal_sync();
    Result branch_sync();

    int is_manifest_modified(bool &modified);

    //! Process one repository
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    virtual int process_repo();

    //! Fetch and/or update one existing repository
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    virtual int fetch_update();

    //! Set the git instance
    /*!
     * \param[in] git the git instance
     */
    void set_git(std::shared_ptr<GitBase> git);

    //! Get the git instance
    /*!
     * \return the git instance
     */
    std::shared_ptr<GitBase> get_git() const;

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

private:
    //!< \cond DOXY_IMPL
    std::shared_ptr<ConfigFolder> m_config_folder; //!< The config folder
    std::shared_ptr<GitBase> m_git;                //!< The git instance
    log::Level m_log_level = log::Level::INFO;     //!< The log level
    std::string m_branch;                          //!< The branch to sync
    bool m_force = false;                          //!< Force the operation
    //!< \endcond
};

} // namespace manifest

} // namespace repo

} // namespace esys
