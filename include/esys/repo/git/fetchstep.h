/*!
 * \file esys/repo/git/fetchstep.h
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

//<swig_inc/>

namespace esys
{

namespace repo
{

namespace git
{

enum class FetchStep
{
    NOT_SET,
    ENUMERATING,
    COUNTING,
    COMPRESSING,
    TOTAL,
    RECEIVING,
    RESOLVING,
    UPDATE_TIPS
};

} // namespace git

} // namespace repo

} // namespace esys
