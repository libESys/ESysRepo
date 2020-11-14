/*!
 * \file esys/repo/libgit2/gitimpl.h
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
#include "esys/repo/libgit2/git.h"
#include "esys/repo/libgit2/libgit2.h"
#include "esys/repo/libgit2/guard.h"

#include <git2.h>

#include <memory>

namespace esys
{

namespace repo
{

namespace libgit2
{

class ESYSREPO_API GitImpl
{
public:
    GitImpl(Git *self);
    ~GitImpl();

    int open(const std::string &folder);
    int close();
    int get_remotes(std::vector<git::Remote> &remotes);
    int get_branches(std::vector<git::Branch> &branches, git::BranchType branch_type = git::BranchType::LOCAL);

    int clone(const std::string &url, const std::string &path);
    int checkout(const std::string &branch, bool force = false);

    int check_error(int result, const std::string &action = "");

    Git *self() const;

    static int libgit2_credentials(git_credential **out, const char *url, const char *name, unsigned int types,
                                   void *payload);
    static bool is_ssh_agent_running();

protected:
    static std::unique_ptr<LibGit2> s_libgt2;

    Git *m_self = nullptr;
    git_repository *m_repo = nullptr;
    Guard<git_credential> m_credential;
};

} // namespace libgit2

} // namespace repo

} // namespace esys
