/*!
 * \file esys/repo/manifest/base.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2021 Michel Gillet
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
#include "esys/repo/manifest/filebase.h"

#include <string>

namespace esys
{

namespace repo
{

namespace manifest
{

/*! \class Base esys/repo/manifest/base.h "esys/repo/manifest/base.h"
 * \brief Base class for all ESysRepo manifest file format
 */
class ESYSREPO_API Base : public FileBase
{
public:
    //! Default constructor
    Base();

    //! Destructor
    virtual ~Base();

    static const std::string &get_folder_name();

private:
    //!< \cond DOXY_IMPL
    static const std::string s_folder_name;
    //!< \endcond
};

} // namespace manifest

} // namespace repo

} // namespace esys
