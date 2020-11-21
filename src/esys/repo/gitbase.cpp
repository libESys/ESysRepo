/*!
 * \file esys/repo/gitbase.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 22020 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/gitbase.h"

#include <boost/filesystem.hpp>

namespace esys
{

namespace repo
{

GitBase::GitBase()
    : log::User()
{
}

GitBase::~GitBase() = default;

bool GitBase::is_repo(const std::string &path)
{
    boost::filesystem::path git_path = path;

    git_path /= ".git";

    return boost::filesystem::exists(git_path);
}

void GitBase::set_id(std::size_t id)
{
    m_id = id;
}

std::size_t GitBase::get_id() const
{
    return m_id;
}

void GitBase::set_debug(bool debug)
{
    m_debug = debug;
}

bool GitBase::get_debug() const
{
    return m_debug;
}

} // namespace repo

} // namespace esys
