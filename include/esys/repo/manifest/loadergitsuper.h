/*!
 * \file esys/repo/manifest/loadergitsuper.h
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
#include "esys/repo/manifest/loaderbase.h"

namespace esys
{

namespace repo
{

namespace manifest
{

/*! \class LoaderGitSuper esys/repo/manifest/loadergitsuper.h "esys/repo/manifest/loadergitsuper.h"
 * \brief Load a git super project
 */
class ESYSREPO_API LoaderGitSuper : public LoaderBase
{
public:
    //! Default constructor
    LoaderGitSuper();

    //! Destructor
    virtual ~LoaderGitSuper();

    int run() override;
};

} // namespace manifest

} // namespace repo

} // namespace esys
