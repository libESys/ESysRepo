// PySwig 0.1.0

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

#include <string>

//<swig_inc>
%{
#include "esys/repo/manifest/type.h"
%}
//</swig_inc>

namespace esys::repo::manifest
{

enum class Type
{
    NOT_SET,
    UNKNOWN,
    GOOGLE_MANIFEST,
    ESYSREPO_MANIFEST,
    GIT_SUPER_PROJECT
};

ESYSREPO_API int convert(Type type, std::string &text);
ESYSREPO_API int convert(const std::string &text, Type &type);

} // namespace esys::repo::manifest