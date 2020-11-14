/*!
 * \file esys/repo/libgit2/guardrelease_libgit2.cpp
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
#include "esys/repo/libgit2/guardrelease.h"

namespace esys
{

namespace repo
{

namespace libgit2
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

} // namespace libgit2

} // namespace repo

} // namespace esys
