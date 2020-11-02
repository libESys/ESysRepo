/*!
 * \file esys/repo/git/branch.h
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
#include "esys/repo/git/branchtype.h"

#include <string>

namespace esys
{

namespace repo
{

namespace git
{

class ESYSREPO_API Branch
{
public:
    Branch();
    virtual ~Branch();

    void set_name(const std::string &name);
    const std::string &get_name() const;

    void set_type(BranchType type);
    BranchType get_type() const;

    void set_is_head(bool is_head);
    bool get_is_head() const;

protected:
    std::string m_name;
    BranchType m_type = BranchType::NOT_SET;
    bool m_is_head = false;
};

} // namespace git

} // namespace repo

} // namespace esys
