/*!
 * \file esys/repo/progresscallbackbase.h
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
#include "esys/repo/git/progress.h"

//<swig_inc/>

namespace esys
{

namespace repo
{

class ESYSREPO_API ProgressCallbackBase
{
public:
    ProgressCallbackBase();
    virtual ~ProgressCallbackBase();

    virtual void git_progress_notif(const git::Progress &progress) = 0;
};

} // namespace repo

} // namespace esys
