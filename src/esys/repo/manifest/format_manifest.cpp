/*!
 * \file esys/repo/manifest/format_manifest.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/manifest/format.h"

namespace esys
{

namespace repo
{

namespace manifest
{

int convert(Format format, std::string &text)
{
    switch (format)
    {
        case Format::XML: text = "xml"; break;
        case Format::JSON: text = "json"; break;
        default: return -1;
    }
    return 0;
}

int convert(const std::string &text, Format &format)
{
    if (text == "xml")
        format = Format::XML;
    else if (text == "json")
        format = Format::JSON;
    else
    {
        format = Format::UNKNOWN;
        return -1;
    }
    return 0;
}

} // namespace manifest

} // namespace repo

} // namespace esys
