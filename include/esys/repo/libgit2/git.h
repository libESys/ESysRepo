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

    int open(const std::string &folder) override;
    bool is_open() override;

    int close() override;
    int get_remotes(std::vector<git::Remote> &remotes) override;
    int get_branches(std::vector<git::Branch> &branches, git::BranchType branch_type = git::BranchType::LOCAL) override;

    int clone(const std::string &url, const std::string &path) override;
    int checkout(const std::string &branch, bool force = false) override;

    int get_last_commit(git::Commit &commit) override;

    int is_dirty(bool &dirty) override;

    int get_status(git::RepoStatus &repo_status) override;

    bool is_ssh_agent_running() override;
  
    const std::string &get_version() override;
    const std::string &get_lib_name() override;

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
    //!< \endcond
};

} // namespace libgit2

#ifdef ESYSREPO_USE_LIBGIT2
using namespace libgit2;
#endif

} // namespace repo

} // namespace esys
