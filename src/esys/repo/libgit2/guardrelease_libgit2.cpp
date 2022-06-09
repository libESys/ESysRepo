/*!
 * \file esys/repo/libgit2/guardrelease_libgit2.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/libgit2/guardrelease.h"

namespace esys::repo::libgit2
{

template<>
ESYSREPO_API void guard_release<git_remote>(git_remote *remote)
{
    if (remote == nullptr) return;
    git_remote_free(remote);
}

template<>
ESYSREPO_API void guard_release<git_branch_iterator>(git_branch_iterator *branch_iterator)
{
    if (branch_iterator == nullptr) return;
    git_branch_iterator_free(branch_iterator);
}

template<>
ESYSREPO_API void guard_release<git_reference>(git_reference *reference)
{
    if (reference == nullptr) return;
    git_reference_free(reference);
}

template<>
ESYSREPO_API void guard_release<git_object>(git_object *object)
{
    if (object == nullptr) return;
    git_object_free(object);
}

template<>
ESYSREPO_API void guard_release<git_credential>(git_credential *credential)
{
    if (credential == nullptr) return;
    git_credential_free(credential);
}

template<>
ESYSREPO_API void guard_release<git_commit>(git_commit *commit)
{
    if (commit == nullptr) return;
    git_commit_free(commit);
}

template<>
ESYSREPO_API void guard_release<git_status_list>(git_status_list *status_list)
{
    if (status_list == nullptr) return;
    git_status_list_free(status_list);
}

template<>
ESYSREPO_API void guard_release<git_annotated_commit>(git_annotated_commit *annotated_commit)
{
    if (annotated_commit == nullptr) return;
    git_annotated_commit_free(annotated_commit);
}

template<>
ESYSREPO_API void guard_release<git_revwalk>(git_revwalk *walker)
{
    if (walker == nullptr) return;
    git_revwalk_free(walker);
}

template<>
ESYSREPO_API void guard_release<git_tree>(git_tree *tree)
{
    if (tree == nullptr) return;

    git_tree_free(tree);
}

template<>
ESYSREPO_API void guard_release<git_diff>(git_diff *diff)
{
    if (diff == nullptr) return;

    git_diff_free(diff);
}

template<>
ESYSREPO_API void guard_release<git_diff_stats>(git_diff_stats *diff_stats)
{
    if (diff_stats == nullptr) return;

    git_diff_stats_free(diff_stats);
}

} // namespace esys::repo::libgit2
