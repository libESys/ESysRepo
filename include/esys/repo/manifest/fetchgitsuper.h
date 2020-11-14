/*!
 * \file esys/repo/manifest/fetchgitsuper.h
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
#include "esys/repo/manifest/fetchbase.h"

namespace esys
{

namespace repo
{

namespace manifest
{

class ESYSREPO_API FetchGitSuper : public FetchBase
{
public:
    FetchGitSuper();
    virtual ~FetchGitSuper();

    int run() override;
};

} // namespace manifest

} // namespace repo

} // namespace esys
