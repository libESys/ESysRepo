/*!
 * \file esys/repo/manifest/format.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2021-2022 Michel Gillet
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

enum class Format
{
    NOT_SET,
    UNKNOWN,
    XML,
    JSON
};

ESYSREPO_API Result convert(Format format, std::string &text);        //<swig_out/>
ESYSREPO_API Result convert(const std::string &text, Format &format); //<swig_out/>

//<swig>%rename(convert_format_to_text) convert;</swig>
ESYSREPO_API std::string convert(Format format);

//<swig>%rename(convert_text_to_format) convert;</swig>
ESYSREPO_API Format convert(const std::string &text);

} // namespace esys::repo::manifest
