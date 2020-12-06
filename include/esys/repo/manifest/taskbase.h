/*!
 * \file esys/repo/manifest/taskbase.h
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
#include "esys/repo/configfolder.h"
#include "esys/repo/manifest/repository.h"
#include "esys/repo/git/progress.h"
#include "esys/repo/progresscallback_t.h"

#include <string>
#include <memory>
#include <vector>
#include <mutex>

namespace esys
{

namespace repo
{

namespace manifest
{

/*! \class TaskBase esys/repo/manifest/taskbase.h "esys/repo/manifest/taskbase.h"
 * \brief Base class for all Tasks
 */
class ESYSREPO_API TaskBase
{
public:
    //! Default constructor
    TaskBase();

    //! Destructor
    virtual ~TaskBase();

    //! Set the git instance to use
    /*!
     * \param[in] git the git instance
     */
    virtual void set_git(std::shared_ptr<GitBase> git);

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

    void set_repo(std::shared_ptr<Repository> repo);
    std::shared_ptr<Repository> get_repo();

    void set_result(int result);
    int get_result() const;

    void clear_errors();
    void add_errors(const std::string &error);
    std::vector<std::string> &get_errors();
    const std::vector<std::string> &get_errors() const;

    void set_id(std::size_t id);
    std::size_t get_id() const;

    void git_progress_notif(const git::Progress &progress);

    void get_progress(git::Progress &progress);

    virtual int run() = 0;

protected:
    //!< \cond DOXY_IMPL
    std::shared_ptr<ConfigFolder> m_config_folder; //!< The config folder
    std::shared_ptr<GitBase> m_git;                //!< The git instance
    std::shared_ptr<Repository> m_repo;            //!< The git repository to process
    int m_result = 0;
    std::vector<std::string> m_errors;
    std::size_t m_id = 0;
    git::Progress m_progress;
    ProgressCallback_t<TaskBase> m_progress_callback{this, &TaskBase::git_progress_notif};
    std::mutex m_progress_mutex;
    //!< \endcond
};

} // namespace manifest

} // namespace repo

} // namespace esys
