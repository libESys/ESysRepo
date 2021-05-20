/*!
 * \file esys/repo/git/branches_git.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2021 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/git/branches.h"

#include <algorithm>

namespace esys
{

namespace repo
{

namespace git
{

Branches::Branches()
{
}

Branches::Branches(const std::vector<Branch> &branches)
{
    for (auto &branch_raw : branches)
    {
        std::shared_ptr<Branch> branch = std::make_shared<Branch>(branch_raw);

        add(branch);
    }
}

Branches::~Branches()
{
}

void Branches::add(std::shared_ptr<Branch> branch)
{
    m_branches.push_back(branch);
    if (branch->get_is_head()) m_head = branch;
}

void Branches::clear()
{
    m_head = nullptr;
    m_branches.clear();
}

std::shared_ptr<Branch> Branches::get_head()
{
    return m_head;
}

std::size_t Branches::size() const
{
    return m_branches.size();
}

void Branches::sort()
{
    auto head_first = [](const std::shared_ptr<git::Branch> b0, const std::shared_ptr<git::Branch> b1) -> bool { return b0->get_is_head(); };

    std::sort(get().begin(), get().end(), head_first);
}

std::vector<std::shared_ptr<Branch>> &Branches::get()
{
    return m_branches;
}

const std::vector<std::shared_ptr<Branch>> &Branches::get() const
{
    return m_branches;
}

std::shared_ptr<Branch> Branches::find(const std::string &name)
{
    for (auto branch : get())
    {
        if (branch->get_name() == name) return branch;
    }
    return nullptr;
}

} // namespace git

} // namespace repo

} // namespace esys
