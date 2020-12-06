/*!
 * \file esys/repo/git/updatetiptype.h
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

#include <string>

//<swig_inc/>

namespace esys
{

namespace repo
{

namespace git
{

enum class UpdateTipType
{
    NOT_SET,
    NEW,
    UPDATE
};

} // namespace git

} // namespace repo

} // namespace esys
