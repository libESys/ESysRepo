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

namespace esys
{

namespace repo
{

namespace manifest
{

enum Type
{
    NOT_SET,
    UNKNOWN,
    GOOGLE_MANIFEST,
    ESYSREPO_MANIFEST,
    GIT_SUPER_PROJECT
};

int convert(Type type, std::string &text);
int convert(const std::string &text, Type &type);

} // namespace manifest

} // namespace repo

} // namespace esys
