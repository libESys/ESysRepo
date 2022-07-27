/*!
 * \file esys/repo/manifest/kind_manifest.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/manifest/kind.h"

namespace esys::repo::manifest
{

Result convert(Kind type, std::string &text)
{
    switch (type)
    {
        case Kind::ISOLATED: text = "isolated"; break;
        case Kind::EMBEDDED: text = "embedded"; break;
        default: return ESYSREPO_RESULT(ResultCode::MANIFEST_KIND_UNKNOWN);
    }
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result convert(const std::string &text, Kind &kind)
{
    if (text == "isolated")
        kind = Kind::ISOLATED;
    else if (text == "embedded")
        kind = Kind::EMBEDDED;
    else
    {
        kind = Kind::UNKNOWN;
        return ESYSREPO_RESULT(ResultCode::MANIFEST_KIND_UNKNOWN);
    }
    return ESYSREPO_RESULT(ResultCode::OK);
}

} // namespace esys::repo::manifest
