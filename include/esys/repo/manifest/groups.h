/*!
 * \file esys/repo/manifest/groups.h
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

#pragma once

#include "esys/repo/esysrepo_defs.h"
#include "esys/repo/manifest/group.h"

#include <string>
#include <vector>
#include <memory>
#include <map>

namespace esys
{

namespace repo
{

namespace manifest
{

/*! \class Groups esys/repo/manifest/groups.h "esys/repo/manifest/groups.h"
 * \brief Hold all Group found in ESysRepo manifest
 */
class ESYSREPO_API Groups : public std::enable_shared_from_this<Groups>
{
public:
    //! Default constructor
    Groups();

    //! Destructor
    virtual ~Groups();

    //! Add a group
    /*!
     * \param[in] repo the repository
     */
    void add_group(std::shared_ptr<Group> group);

    //! Get all Groups
    /*!
     * \return all Groups
     */
    std::vector<std::shared_ptr<Group>> &get_groups();

    //! Get all Groups
    /*!
     * \return all Groups
     */
    const std::vector<std::shared_ptr<Group>> &get_groups() const;

    std::shared_ptr<Group> find_group_by_name(const std::string &name);
    std::shared_ptr<Group> find_or_new_group_by_name(const std::string &name);

protected:
    //!< \cond DOXY_IMPL
    std::vector<std::shared_ptr<Group>> m_groups; //!< All Groups
    std::map<std::string, std::shared_ptr<Group>> m_map_groups_by_name;
    //!< \endcond
};

} // namespace manifest

} // namespace repo

} // namespace esys
