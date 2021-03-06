/*!
 * \file esys/repo/libgit2/git.h
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
#include "esys/repo/gitbase.h"

#include <memory>

//<swig_inc/>

//<swig>%shared_ptr(esys::repo::libgit2::Git);</swig>

namespace esys::repo
{

namespace libgit2
{

class ESYSREPO_API GitImpl;

/*! \class Git esys/build/libgit2/git.h "esys/build/libgit2/git.h"
 * \brief Git client implementation based on libgit2
 */
class ESYSREPO_API Git : public GitBase
{
public:
    //! Default constructor
    Git();

    //! Destructor
    ~Git() override;

    static std::shared_ptr<GitBase> new_ptr();

    //<swig>%rename(open_folder) open;</swig>
    Result open(const std::string &folder) override;
    bool is_open() override;

    Result close() override;
    Result get_remotes(std::vector<git::Remote> &remotes) override;
    Result get_branches(git::Branches &branches, git::BranchType branch_type = git::BranchType::LOCAL) override;

    Result clone(const std::string &url, const std::string &path, const std::string &branch = "") override;
    Result checkout(const std::string &branch, bool force = false) override;
    Result reset(const git::CommitHash &commit, git::ResetType type = git::ResetType::SOFT) override;
    Result fastforward(const git::CommitHash &commit) override;

    Result get_last_commit(git::CommitHash &commit) override;
    Result get_parent_commit(const git::CommitHash &commit, git::CommitHash &parent, int nth_parent = 1) override;

    Result is_dirty(bool &dirty) override;
    Result is_detached(bool &detached) override;

    Result get_status(git::RepoStatus &repo_status) override;

    bool is_ssh_agent_running(bool log_once = true) override;
    void detect_ssh_agent(bool log_once = true) override;

    Result merge_analysis(const std::vector<std::string> &refs, git::MergeAnalysisResult &merge_analysis_result,
                          std::vector<git::CommitHash> &commits) override;

    Result fetch(const std::string &remote = "") override;

    bool has_branch(const std::string &name, git::BranchType branch_type = git::BranchType::LOCAL) override;

    Result get_hash(const std::string &revision, std::string &hash,
                    git::BranchType branch_type = git::BranchType::REMOTE) override;

    Result walk_commits(std::shared_ptr<git::WalkCommit> walk_commit) override;

    Result diff(const git::CommitHash commit_hash, std::shared_ptr<git::Diff> diff) override;

    void set_url(const std::string &url);
    const std::string &get_url();

    void set_folder(const std::string &folder);
    const std::string &get_folder();

    const std::string &get_version() override;
    const std::string &get_lib_name() override;

    void debug(int level, const std::string &msg) override;

    //! Get the version of the git library used
    /*!
     * \return the version of the git library
     */
    static const std::string &s_get_version();

    //! Get the name of the git library
    /*!
     * \return the name of the git library
     */
    static const std::string &s_get_lib_name();

    //! Get the version of the ssh library
    /*!
     * \return the version of the ssh library
     */
    static const std::string &s_get_ssh_version();

    //! Get the name of the ssh library
    /*!
     * \return the name of the ssh library
     */
    static const std::string &s_get_ssh_lib_name();

    //! Get the PIMPL
    /*!
     * \return the PIMPL
     */
    GitImpl *get_impl() const;

    void set_logger_if(std::shared_ptr<log::Logger_if> logger_if) override;

private:
    //!< \cond DOXY_IMPL
    std::unique_ptr<GitImpl> m_impl; //!< the PIMPL
    std::string m_url;
    std::string m_folder;
    static bool s_detect_ssh_agent_done;
    static bool s_ssh_agent_running;
    //!< \endcond
};

} // namespace libgit2

#ifdef ESYSREPO_USE_LIBGIT2
using namespace libgit2;
#endif

} // namespace esys::repo
