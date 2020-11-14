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

class ESYSREPO_API Git : public GitBase
{
public:
    Git();
    virtual ~Git();

    int open(const std::string &folder) override;

    int close() override;
    int get_remotes(std::vector<git::Remote> &remotes) override;
    int get_branches(std::vector<git::Branch> &branches, git::BranchType branch_type = git::BranchType::LOCAL) override;

    int clone(const std::string &url, const std::string &path) override;
    int checkout(const std::string &branch, bool force = false) override;

    GitImpl *get_impl() const;

protected:
    std::unique_ptr<GitImpl> m_impl;
};

} // namespace libgit2

} // namespace repo

} // namespace esys
