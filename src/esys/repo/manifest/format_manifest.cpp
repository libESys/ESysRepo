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

namespace esys::repo::manifest
{

Result convert(Format format, std::string &text)
{
    switch (format)
    {
        case Format::XML: text = "xml"; break;
        case Format::JSON: text = "json"; break;
        default: return ESYSREPO_RESULT(ResultCode::MANIFEST_FORMAT_UNKNOWN);
    }
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result convert(const std::string &text, Format &format)
{
    if (text == "xml")
        format = Format::XML;
    else if (text == "json")
        format = Format::JSON;
    else
    {
        format = Format::UNKNOWN;
        return ESYSREPO_RESULT(ResultCode::MANIFEST_FORMAT_UNKNOWN);
    }
    return ESYSREPO_RESULT(ResultCode::OK);
}

ESYSREPO_API std::string convert(Format format)
{
    std::string text;
    auto result = convert(format, text);
    if (result.error()) return "";
    return text;
}

ESYSREPO_API Format convert(const std::string &text)
{
    Format format;
    Result result = convert(text, format);
    if (result.error()) return Format::NOT_SET;
    return format;
}

} // namespace esys::repo::manifest
