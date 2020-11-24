/*!
 * \file esys/repo/git/mergeanalysisresult.h
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

enum class MergeAnalysisResult
{
    NOT_SET,

    //! No merge is possible.  (Unused.)
    NONE,

    //! A "normal" merge
    /*!
     * Both HEAD and the given merge input have diverged
     * from their common ancestor.  The divergent commits must be merged.
     */
    NORMAL,

    //! Up to date, no merge required
    /*!
     * All given merge inputs are reachable from HEAD, meaning the
     * repository is up-to-date and no merge needs to be performed.
     */
    UP_TO_DATE,

    //! Only a fastforward "merge" is needed
    /*!
     * The given merge input is a fast-forward from HEAD and no merge
     * needs to be performed.  Instead, the client can check out the
     * given merge input.
     */
    FASTFORWARD,

    //! The HEAD of the current repository doesn not point to a valid commit
    /*!
     * The HEAD of the current repository is "unborn".
     * No merge can be performed, but the caller may wish
     * to simply set HEAD to the target commit(s).
     */
    UNBORN,
};

} // namespace git

} // namespace repo

} // namespace esys
