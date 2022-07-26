/*!
 * \file esys/repo/git/url_git.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2022 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/git/url.h"

#include <Poco/URI.h>

namespace esys::repo::git
{

URL::URL() = default;

URL::URL(const std::string &url)
    : m_url(url)
{
}

URL::~URL() = default;

void URL::set(const std::string &url)
{
    m_url = url;
}

const std::string &URL::get() const
{
    return m_url;
}

void URL::remove_dot_git(std::string &text)
{
    auto idx = text.rfind(".git");
    if (idx == text.npos) return;

    text = text.substr(0, idx);
}

bool URL::operator==(const URL &url) const
{
    return operator==(url.get());
}

bool URL::operator==(const std::string &url) const
{
    std::string url_ = url;
    std::string this_url = get();

    remove_dot_git(url_);
    remove_dot_git(this_url);

    Poco::URI uri(url_);
    Poco::URI this_uri(this_url);

    if ((this_uri.getAuthority() == uri.getAuthority()) && (this_uri.getPath() == uri.getPath())) return true;
    if ((this_uri.getHost() == uri.getHost()) && (this_uri.getPath() == uri.getPath())) return true;

    return false;
}

bool URL::operator!=(const URL &url) const
{
    return !operator==(url);
}

bool URL::operator!=(const std::string &url) const
{
    return !operator==(url);
}

} // namespace esys::repo::git
