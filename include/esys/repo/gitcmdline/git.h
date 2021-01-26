/*!
 * \file esys/repo/gitcmdline/git.h
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
#include "esys/repo/gitbase.h"

namespace esys
{

namespace repo
{

namespace gitcmdline
{

class ESYSREPO_API Git : public GitBase
{
public:
    Git();
    virtual ~Git();
};

} // namespace gitcmdline

} // namespace repo

} // namespace esys
