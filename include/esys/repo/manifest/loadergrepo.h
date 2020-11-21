/*!
 * \file esys/repo/manifest/loadergrepo.h
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

/*! \class LoaderGRepo esys/repo/manifest/loadergrepo.h "esys/repo/manifest/loadergrepo.h"
 * \brief Load a Google repo tool manifest
 */
class ESYSREPO_API LoaderGRepo : public LoaderBase
{
public:
    //! Default constructor
    LoaderGRepo();

    //! Destructor
    virtual ~LoaderGRepo();

    int run() override;
};

} // namespace manifest

} // namespace repo

} // namespace esys
