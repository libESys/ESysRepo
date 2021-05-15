/*!
 * \file esys/repo/libgit2/guardsrelease_libgit2.cpp
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
#include "esys/repo/libgit2/guardsrelease.h"

namespace esys
{

namespace repo
{

namespace libgit2
{

template<>
ESYSREPO_API void guards_release<git_strarray>(git_strarray *data)
{
    if (data == nullptr) return;
    git_strarray_dispose(data);
}

} // namespace libgit2

} // namespace repo

} // namespace esys
