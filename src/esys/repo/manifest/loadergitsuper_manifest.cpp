/*!
 * \file esys/repo/manifest/loadergitsuper_manifest.cpp
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
#include "esys/repo/manifest/loadergitsuper.h"

namespace esys::repo::manifest
{

LoaderGitSuper::LoaderGitSuper()
    : LoaderBase()
{
}

LoaderGitSuper::~LoaderGitSuper() = default;

Result LoaderGitSuper::run()
{
    return ESYSREPO_RESULT(ResultCode::NOT_IMPLEMENTED);
}

} // namespace esys::repo::manifest
