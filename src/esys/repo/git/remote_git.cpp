/*!
 * \file esys/repo/git/remote_git.cpp
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
#include "esys/repo/git/remote.h"

namespace esys::repo::git
{

Remote::Remote() = default;

Remote::~Remote() = default;

void Remote::set_name(const std::string &name)
{
    m_name = name;
}

const std::string &Remote::get_name() const
{
    return m_name;
}

void Remote::set_url(const std::string &url)
{
    m_url = url;
}

const std::string &Remote::get_url() const
{
    return m_url;
}

} // namespace esys::repo::git
