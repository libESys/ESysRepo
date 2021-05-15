/*!
 * \file esys/repo/libgit2/guardsrelease.h
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
void guards_release(T *data)
{
    assert(false);
}

template<>
ESYSREPO_API void guards_release<git_strarray>(git_strarray *data);

} // namespace libgit2

} // namespace repo

} // namespace esys
