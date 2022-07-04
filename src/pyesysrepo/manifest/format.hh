// PySwig 0.1.0

/*!
 * \file esys/repo/manifest/format.h
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

#include <string>

//<swig_inc>
%{
#include "esys/repo/manifest/format.h"
%}
//</swig_inc>

namespace esys::repo::manifest
{

enum class Format
{
    NOT_SET,
    UNKNOWN,
    XML,
    JSON
};

// ESYSREPO_API int convert(Format format, std::string &text);        //<swig_out/>
// ESYSREPO_API int convert(const std::string &text, Format &format); //<swig_out/>

%rename(convert_format_to_text) convert;    //<swig>%rename(convert_format_to_text) convert;</swig>
ESYSREPO_API std::string convert(Format format);

%rename(convert_text_to_format) convert;    //<swig>%rename(convert_text_to_format) convert;</swig>
ESYSREPO_API Format convert(const std::string &text);

} // namespace esys::repo::manifest
