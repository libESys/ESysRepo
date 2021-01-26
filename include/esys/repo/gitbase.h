/*!
 * \file esys/repo/gitbase.h
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
#include "esys/repo/git/remote.h"
#include "esys/repo/git/branch.h"
#include "esys/repo/git/commit.h"
#include "esys/repo/git/repostatus.h"
#include "esys/repo/git/mergeanalysisresult.h"
#include "esys/repo/git/fetchstep.h"
#include "esys/repo/git/progress.h"
#include "esys/repo/progresscallbackbase.h"

#include <esys/log/user.h>

#include <mutex>
#include <string>
#include <vector>
#include <chrono>

//<swig_inc/>

namespace esys
{

namespace repo
{

/*! \class GitBase esys/repo/gitbase.h "esys/repo/gitbase.h"
 * \brief Base class for git client implementation
 */
class ESYSREPO_API GitBase : public log::User
{
public:
    typedef std::shared_ptr<GitBase> (*GeneratorType)();

    //! Default constructor
    GitBase();

    //! Destructor
    virtual ~GitBase();

    //! Open a git repository for inspection
    /*!
     * \param[in] folder the folder where is the git repository
     * \return 0 if successful, < 0 otherwise
     */
    virtual int open(const std::string &folder) = 0;

    //! Tells if the git repository is open or not
    /*!
     * \return true if open, false otherwise
     */
    virtual bool is_open() = 0;

    //! Close a git repository
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    virtual int close() = 0;

    //! Get all remotes of an open git repository
    /*!
     * \param[out] remotes vector with all the remotes of the open git repository
     * \return 0 if successful, < 0 otherwise
     */
    virtual int get_remotes(std::vector<git::Remote> &remotes) = 0;

    //! Get all branches of an open git repository
    /*!
     * \param[out] branches vector with all the branches of the open git repository
     * \param[in] branch_type tells if the local or remote branches are requested
     * \return 0 if successful, < 0 otherwise
     */
    virtual int get_branches(std::vector<git::Branch> &branches,
                             git::BranchType branch_type = git::BranchType::LOCAL) = 0;

    //! Clone a remote git repository given it's address and path where to clone it
    /*!
     * \param[in] url the url for the repository to clone
     * \param[in] path where to clone the repository
     * \return 0 if successful, < 0 otherwise
     */
    virtual int clone(const std::string &url, const std::string &path) = 0;

    //! Checkout a given branch of an open git repository
    /*!
     * \param[in] branch the name of the branch to checkout
     * \param[in] force if the cloing will be forced or not
     * \return 0 if successful, < 0 otherwise
     */
    virtual int checkout(const std::string &branch, bool force = false) = 0;

    //! Get the last commit of the HEAD
    /*!
     * \param[out] commit the commit data
     * \return 0 if successful, < 0 otherwise
     */
    virtual int get_last_commit(git::Commit &commit) = 0;

    //! Tells if there are changes in the git repo
    /*!
     * \param[out] dirtay true if the git repo is dirty, there are modification; false otherwise
     * \return 0 if successful, < 0 otherwise
     */
    virtual int is_dirty(bool &dirty) = 0;

    //! Get the status of the repository
    /*!
     * \param[out] status the status of the repository
     * \return 0 if successful, < 0 otherwise
     */
    virtual int get_status(git::RepoStatus &status) = 0;

    virtual bool is_ssh_agent_running() = 0;

    virtual int merge_analysis(const std::vector<std::string> &refs, git::MergeAnalysisResult &merge_analysis_result,
                               std::vector<git::Commit> &commits) = 0;

    virtual int fetch(const std::string &remote = "") = 0;

    //! Tells if a folder is a git repository
    /*!
     * \param[in] path the path of the folder
     * \return true if it's a git repository, false otherwise
     */
    static bool is_repo(const std::string &path);

    //! Set the id of this instance
    /*!
     * \param[in] id the id of this instance
     */
    void set_id(std::size_t id);

    //! Get the id of this instance
    /*!
     * \return the id of this instance
     */
    std::size_t get_id() const;

    //! Set if debug information should be printed
    /*!
     * \param[in] debug true if debug information should be printed
     */
    void set_debug(bool debug);

    //! Get if debug information should be printed
    /*!
     * \return true if debug information should be printed, false otherwise
     */
    bool get_debug() const;

    //! Get the version of the library used to implement the functionality
    /*!
     * \return the version of the library used to implement the functionality
     */
    virtual const std::string &get_version() = 0;

    //! Get the name of the library used to implement the functionality
    /*!
     * \return the name of the library used to implement the functionality
     */
    virtual const std::string &get_lib_name() = 0;

    int handle_sideband_progress(const std::string &text);
    int handle_transfer_progress(const git::Progress &progress);

    void set_progress(const git::Progress &progress);
    void get_progress(git::Progress &progress);

    void set_progress_callback(ProgressCallbackBase *progress_callback);
    ProgressCallbackBase *get_progress_callback();

    //! Sort the branches such that the current one is the first one
    /*!
     * \param[in] branches the branches to sort
     */
    static void sort_branches(std::vector<git::Branch> &branches);

    //! Decode the information sent by the remote git server
    /*!
     * \param[in] txt the text received
     * \param[out] fetch_step the fetch step we are at
     * \param[out] done true if the detected fetch step is done
     * \param[out] percentage the percentange done of the detected fetch step
     * \return 0 if the decoding was successful, < 0 if an error occurred
     */
    static int decode_sideband_progress(const std::string &txt, git::Progress &progress);

    virtual void cmd_start();
    virtual void cmd_end();
    virtual void open_time();
    virtual void close_time();
    virtual uint64_t get_open_time();
    virtual uint64_t get_last_cmd_elapsed_time();

protected:
    //!< \cond DOXY_IMPL
    std::size_t m_id = 0; //!< The id of the git repository handled
    bool m_debug = false; //!< Trus if debug information should be printed
    git::Progress m_progress;
    ProgressCallbackBase *m_progress_callback = nullptr;
    std::mutex m_progress_mutex;
    std::chrono::time_point<std::chrono::steady_clock> m_open_time;
    std::chrono::time_point<std::chrono::steady_clock> m_last_cmd_start_time;
    std::chrono::time_point<std::chrono::steady_clock> m_last_cmd_end_time;
    std::chrono::time_point<std::chrono::steady_clock> m_close_time;
    //!< \endcond
};

} // namespace repo

} // namespace esys
