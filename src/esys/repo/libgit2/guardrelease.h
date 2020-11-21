/*!
 * \file esys/repo/libgit2/guardrelease.h
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

#include <git2.h>

#include <memory>

namespace esys
{

namespace repo
{

namespace libgit2
{

template<typename T>
void guard_release(T *data)
{
}

template<>
ESYSREPO_API void guard_release<git_remote>(git_remote *data);

template<>
ESYSREPO_API void guard_release<git_branch_iterator>(git_branch_iterator *branch_iterator);

template<>
ESYSREPO_API void guard_release<git_reference>(git_reference *reference);

template<>
ESYSREPO_API void guard_release<git_object>(git_object *object);

template<>
ESYSREPO_API void guard_release<git_credential>(git_credential *credential);

template<>
ESYSREPO_API void guard_release<git_commit>(git_commit *commit);

template<>
ESYSREPO_API void guard_release<git_status_list>(git_status_list *status_list);

} // namespace libgit2

} // namespace repo

} // namespace esys
