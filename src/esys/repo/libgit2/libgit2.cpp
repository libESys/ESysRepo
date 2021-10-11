/*!
 * \file esys/repo/libgit2/libgit2.cpp
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
#include "esys/repo/libgit2/libgit2.h"

#include <git2.h>

#include <iostream>

namespace esys::repo::libgit2
{

LibGit2::LibGit2()
{
    git_libgit2_init();
}

LibGit2::~LibGit2()
{
    git_libgit2_shutdown();
}

} // namespace esys::repo::libgit2
