/*!
 * \file esys/repo/libgit2/git_libgit2.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/libgit2/git.h"
#include "esys/repo/libgit2/gitimpl.h"

namespace esys
{

namespace repo
{

namespace libgit2
{

Git::Git()
    : GitBase()
{
    m_impl = std::make_unique<GitImpl>(this);
}

Git::~Git() = default;

int Git::open(const std::string &folder)
{
    return get_impl()->open(folder);
}

int Git::close()
{
    return get_impl()->close();
}

int Git::get_remotes(std::vector<git::Remote> &remotes)
{
    return get_impl()->get_remotes(remotes);
}

int Git::get_branches(std::vector<git::Branch> &branches, git::BranchType branch_type)
{
    return get_impl()->get_branches(branches, branch_type);
}

GitImpl *Git::get_impl() const
{
    return m_impl.get();
}

} // namespace libgit2

} // namespace repo

} // namespace esys
