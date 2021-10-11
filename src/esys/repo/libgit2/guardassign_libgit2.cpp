/*!
 * \file esys/repo/libgit2/guardassign_libgit2.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/libgit2/guardassign.h"
#include "esys/repo/libgit2/guard.h"

namespace esys::repo::libgit2
{

template<>
ESYSREPO_API int guard_assign<git_commit>(Guard<git_commit> *dest, const Guard<git_commit> &src)
{
    // If a previous object is guarded, release it
    dest->reset();

    return git_commit_dup(dest->get_p(), src.get());
}

} // namespace esys::repo::libgit2
