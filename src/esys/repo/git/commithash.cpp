/*!
 * \file esys/repo/git/commit.cpp
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
#include "esys/repo/git/commit.h"

namespace esys::repo::git
{

CommitHash::CommitHash() = default;

CommitHash::~CommitHash() = default;

void CommitHash::set_hash(const std::string &hash)
{
    m_hash = hash;
}

const std::string &CommitHash::get_hash() const
{
    return m_hash;
}

std::string &CommitHash::get_hash()
{
    return m_hash;
}

} // namespace esys::repo::git
