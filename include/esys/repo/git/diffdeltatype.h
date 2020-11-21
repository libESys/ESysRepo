/*!
 * \file esys/repo/git/diffdeltatype.h
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

enum class DiffDeltaType
{
    NOT_SET,
    UNMODIFIED, //!< no changes
    ADDED,      //!< entry does not exist in old version
    DELETED,    //!< entry does not exist in new version
    MODIFIED,   //!< entry content changed between old and new
    RENAMED,    //!< entry was renamed between old and new
    COPIED,     //!< entry was copied from another old entry
    IGNORED,    //!< entry is ignored item in workdir
    UNTRACKED,  //!< entry is untracked item in workdir
    TYPECHANGE, //!< type of entry changed between old and new
    UNREADABLE, //!< entry is unreadable
    CONFLICTED, //!< entry in the index is conflicted
};

} // namespace git

} // namespace repo

} // namespace esys
