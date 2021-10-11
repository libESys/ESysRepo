/*!
 * \file esys/build/gitcmdline/git_cmdline.cpp
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
#include "esys/repo/gitcmdline/git.h"

namespace esys::repo::gitcmdline
{

Git::Git()
    : GitBase()
{
}

Git::~Git() = default;

} // namespace esys::repo::gitcmdline
