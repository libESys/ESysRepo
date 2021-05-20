/*!
 * \file esys/repo/manifest/groups_manifest.cpp
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
#include "esys/repo/manifest/groups.h"

namespace esys
{

namespace repo
{

namespace manifest
{

Groups::Groups()
    : std::enable_shared_from_this<Groups>()
{
}

Groups::~Groups()
{
}

void Groups::add_group(std::shared_ptr<Group> group)
{
    get_groups().push_back(group);
    m_map_groups_by_name[group->get_name()] = group;
}

std::vector<std::shared_ptr<Group>> &Groups::get_groups()
{
    return m_groups;
}

const std::vector<std::shared_ptr<Group>> &Groups::get_groups() const
{
    return m_groups;
}

std::shared_ptr<Group> Groups::find_group_by_name(const std::string &name)
{
    auto it = m_map_groups_by_name.find(name);

    if (it == m_map_groups_by_name.end()) return nullptr;
    return it->second;
}

std::shared_ptr<Group> Groups::find_or_new_group_by_name(const std::string &name)
{
    auto group = find_group_by_name(name);

    if (group != nullptr) return group;

    group = std::make_shared<Group>(name);
    add_group(group);
    return group;
}

void Groups::clear()
{
    m_groups.clear();
    m_map_groups_by_name.clear();
}

} // namespace manifest

} // namespace repo

} // namespace esys
