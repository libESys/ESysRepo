/*!
 * \file esys/repo/manifest/kind.h
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

enum class Kind
{
    NOT_SET,
    UNKNOWN,
    ISOLATED, //!< Manifest is in its own git repo
    EMBEDDED  //!< Manifest is embedded in a git repo with source code
};

int convert(Kind type, std::string &text);
int convert(const std::string &text, Kind &kind);

} // namespace manifest

} // namespace repo

} // namespace esys
