/*!
 * \file esys/repo/git/diff_git.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/git/diff.h"

namespace esys::repo::git
{

Diff::Diff() = default;

Diff::~Diff() = default;

void Diff::set_files_changed(unsigned int files_changed)
{
    m_files_changed = files_changed;
}

unsigned int Diff::get_files_changed() const
{
    return m_files_changed;
}

void Diff::set_insertions(unsigned int insertions)
{
    m_insertions = insertions;
}

unsigned int Diff::get_insertions() const
{
    return m_insertions;
}

void Diff::set_deletions(unsigned int deletions)
{
    m_deletions = deletions;
}

unsigned int Diff::get_deletions() const
{
    return m_deletions;
}

void Diff::set_renames(unsigned int renames)
{
    m_renames = renames;
}

unsigned int Diff::get_renames() const
{
    return m_renames;
}

} // namespace esys::repo::git
