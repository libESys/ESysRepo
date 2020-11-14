/*!
 * \file esys/repo/manifest/type_manifest.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/manifest/type.h"

namespace esys
{

namespace repo
{

namespace manifest
{

int convert(Type type, std::string &text)
{
    switch (type)
    {
        case Type::ESYSREPO_MANIFEST: text = "esysrepo"; break;
        case Type::GIT_SUPER_PROJECT: text = "git_super_project"; break;
        case Type::GOOGLE_MANIFEST: text = "grepo"; break;
        default: return -1;
    }
    return 0;
}

int convert(const std::string &text, Type &type)
{
    if (text == "esysrepo")
        type = Type::ESYSREPO_MANIFEST;
    else if (text == "git_super_project")
        type = Type::GIT_SUPER_PROJECT;
    else if (text == "grepo")
        type = Type::GOOGLE_MANIFEST;
    else
    {
        type = Type::UNKNOWN;
        return -1;
    }
    return 0;
}

} // namespace manifest

} // namespace repo

} // namespace esys
