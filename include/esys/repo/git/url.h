/*!
 * \file esys/repo/git/url.h
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

#pragma once

#include "esys/repo/esysrepo_defs.h"

#include <memory>
#include <string>

namespace esys::repo::git
{

class ESYSREPO_API URLImpl;

class ESYSREPO_API URL
{
public:
    URL();
    URL(const std::string &url);
    ~URL();

    void set(const std::string &url);
    const std::string &get() const;

    static void remove_dot_git(std::string &text);

    bool operator==(const URL &url) const;
    bool operator==(const std::string &url) const;

    bool operator!=(const URL &url) const;
    bool operator!=(const std::string &url) const;

    //URLImpl *get_impl();
private:
    //std::shared_ptr<URLImpl> m_impl;
    std::string m_url;
};

} // namespace esys::repo::git
