/*!
 * \file esys/build/libgit2/git.h
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

#include <memory>

namespace esys
{

namespace repo
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
    virtual ~Git();

    static std::shared_ptr<GitBase> new_ptr();

    int open(const std::string &folder) override;
    bool is_open() override;

    int close() override;
    int get_remotes(std::vector<git::Remote> &remotes) override;
    int get_branches(git::Branches &branches, git::BranchType branch_type = git::BranchType::LOCAL) override;

    int clone(const std::string &url, const std::string &path, const std::string &branch = "") override;
    int checkout(const std::string &branch, bool force = false) override;
    int reset(const git::Commit &commit, git::ResetType type = git::ResetType::SOFT) override;
    int fastforward(const git::Commit &commit) override;

    int get_last_commit(git::Commit &commit) override;
    int get_parent_commit(const git::Commit &commit, git::Commit &parent, int nth_parent = 1) override;

    int is_dirty(bool &dirty) override;
    int is_detached(bool &detached) override;

    int get_status(git::RepoStatus &repo_status) override;

    bool is_ssh_agent_running() override;

    int merge_analysis(const std::vector<std::string> &refs, git::MergeAnalysisResult &merge_analysis_result,
                       std::vector<git::Commit> &commits) override;

    int fetch(const std::string &remote = "") override;

    bool has_branch(const std::string &name, git::BranchType branch_type = git::BranchType::LOCAL) override;

    int get_hash(const std::string &revision, std::string &hash,
                 git::BranchType branch_type = git::BranchType::REMOTE) override;

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

protected:
    //!< \cond DOXY_IMPL
    std::unique_ptr<GitImpl> m_impl; //!< the PIMPL
    std::string m_url;
    std::string m_folder;
    //!< \endcond
};

} // namespace libgit2

#ifdef ESYSREPO_USE_LIBGIT2
using namespace libgit2;
#endif

} // namespace repo

} // namespace esys
