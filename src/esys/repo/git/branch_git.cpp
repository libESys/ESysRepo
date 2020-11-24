/*!
 * \file esys/repo/git/branch_git.cpp
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
#include "esys/repo/git/branch.h"

namespace esys
{

namespace repo
{

namespace git
{

Branch::Branch()
{
}

Branch::Branch(const std::string &name, bool is_head)
    : m_name(name)
    , m_is_head(is_head)
{
}

Branch::Branch(const std::string &name, BranchType type, bool is_head)
    : m_name(name)
    , m_type(type)
    , m_is_head(is_head)
{
}

Branch::~Branch()
{
}

void Branch::set_name(const std::string &name)
{
    m_name = name;
}

const std::string &Branch::get_name() const
{
    return m_name;
}

void Branch::set_ref_name(const std::string &ref_name)
{
    m_ref_name = ref_name;
}

const std::string &Branch::get_ref_name() const
{
    return m_ref_name;
}

void Branch::set_type(BranchType type)
{
    m_type = type;
}

BranchType Branch::get_type() const
{
    return m_type;
}

void Branch::set_is_head(bool is_head)
{
    m_is_head = is_head;
}

bool Branch::get_is_head() const
{
    return m_is_head;
}

void Branch::set_remote_branch(const std::string &remote_tracking)
{
    m_remote_branch = remote_tracking;
}

const std::string &Branch::get_remote_branch() const
{
    return m_remote_branch;
}

void Branch::set_remote_name(const std::string &remote_name)
{
    m_remote_name = remote_name;
}

const std::string &Branch::get_remote_name() const
{
    return m_remote_name;
}

} // namespace git

} // namespace repo

} // namespace esys
