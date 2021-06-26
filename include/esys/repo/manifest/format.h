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

namespace esys
{

namespace repo
{

namespace manifest
{

enum class Format
{
    NOT_SET,
    UNKNOWN,
    XML,
    JSON
};

int convert(Format format, std::string &text);
int convert(const std::string &text, Format &format);

} // namespace manifest

} // namespace repo

} // namespace esys
