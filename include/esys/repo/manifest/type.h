/*!
 * \file esys/repo/manifest/type.h
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
#include "esys/repo/result.h"

#include <string>

//<swig_inc/>

namespace esys::repo::manifest
{

enum class Type
{
    NOT_SET,
    UNKNOWN,
    GOOGLE_MANIFEST,    //!< Google repo manifest in ESysRepo folder
    ESYSREPO_MANIFEST,
    GIT_SUPER_PROJECT,
    RAW_GOOGLE_MANIFEST //!< Google repo manifest in Google repo tool folder
};

ESYSREPO_API Result convert(Type type, std::string &text);
ESYSREPO_API Result convert(const std::string &text, Type &type);

} // namespace esys::repo::manifest
