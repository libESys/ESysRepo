/*!
 * \file esys/repo/libgit2/guardrelease.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2022 Michel Gillet
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
void guard_release(T *data)
{
    assert(false);
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

template<>
ESYSREPO_API void guard_release<git_annotated_commit>(git_annotated_commit *annotated_commit);

template<>
ESYSREPO_API void guard_release<git_revwalk>(git_revwalk *walker);

template<>
ESYSREPO_API void guard_release<git_tree>(git_tree *tree);

template<>
ESYSREPO_API void guard_release<git_diff>(git_diff *diff);

template<>
ESYSREPO_API void guard_release<git_diff_stats>(git_diff_stats *diff_stats);

} // namespace libgit2

} // namespace repo

} // namespace esys
