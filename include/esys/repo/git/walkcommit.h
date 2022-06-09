/*!
 * \file esys/repo/git/walkcommit.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2022 Michel Gillet
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
#include "esys/repo/git/commit.h"

#include <memory>

//<swig_inc/>

namespace esys::repo
{

class ESYSREPO_API GitBase;

namespace git
{

/*! \class WalkCommit esys/repo/git/walkcommit.h "esys/repo/git/walkcommit.h"
 * \brief Base class to handle commit walks
 */
class ESYSREPO_API WalkCommit
{
public:
    //! Default constructor
    WalkCommit();

    //! Destructor
    virtual ~WalkCommit();

    virtual int new_commit(GitBase *git_base, std::shared_ptr<Commit> commit) = 0;

private:
    //!< \cond DOXY_IMPL

    //!< \endcond
};

} // namespace git

} // namespace esys::repo
