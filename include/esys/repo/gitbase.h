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

#include <string>
#include <vector>

namespace esys
{

namespace repo
{

class ESYSREPO_API GitBase
{
public:

    GitBase();
    virtual ~GitBase();

    virtual int open(const std::string &folder) = 0;
    virtual int close() = 0;
    virtual int get_remotes(std::vector<git::Remote> &remotes) = 0;
    virtual int get_branches(std::vector<git::Branch> &branches, git::BranchType branch_type = git::BranchType::LOCAL) = 0;

    virtual int clone(const std::string &url, const std::string &path) = 0;
    virtual int checkout(const std::string &branch, bool force = false) = 0;
};

} // namespace build

} // namespace esys