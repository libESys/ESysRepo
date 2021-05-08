/*!
 * \file esys/repo/libgit2/guardassign.h
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

#include <git2.h>

#include <memory>
#include <cassert>

namespace esys
{

namespace repo
{

namespace libgit2
{

template<typename T>
class Guard;

template<typename T>
int guard_assign(Guard<T> *dest, const Guard<T> &src)
{
    assert(false);

    return -1;
}

template<>
ESYSREPO_API int guard_assign<git_commit>(Guard<git_commit> *dest, const Guard<git_commit> &src);

} // namespace libgit2

} // namespace repo

} // namespace esys
