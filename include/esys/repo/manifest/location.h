/*!
 * \file esys/repo/manifest/location.h
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

#pragma once

#include "esys/repo/esysrepo_defs.h"

#include <string>
#include <vector>
#include <memory>

namespace esys
{

namespace repo
{

namespace manifest
{

class ESYSREPO_API Repository;

class ESYSREPO_API Location: public std::enable_shared_from_this<Location>
{
public:
    Location();
    Location(const std::string &name, const std::string &address);
    virtual ~Location();

    void set_name(const std::string &name);
    const std::string &get_name() const;

    void set_address(const std::string &address);
    const std::string &get_address() const;

    std::shared_ptr<Repository> add_repo(const std::string &name, const std::string &path);
    void add_repo(std::shared_ptr<Repository> repo);

    std::vector<std::shared_ptr<Repository>> &get_repos();
    const std::vector<std::shared_ptr<Repository>> &get_repos() const;

protected:
    std::string m_name;
    std::string m_address;
    std::vector<std::shared_ptr<Repository>> m_repos;
};

} // namespace manifest

} // namespace repo

} // namespace esys