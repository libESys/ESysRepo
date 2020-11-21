/*!
 * \file esys/repo/git/difffile_git.cpp
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
#include "esys/repo/git/difffile.h"

namespace esys
{

namespace repo
{

namespace git
{

DiffFile::DiffFile()
{
}

DiffFile::~DiffFile()
{
}

void DiffFile::set_id(const std::string &id)
{
    m_id = id;
}

std::string &DiffFile::get_id()
{
    return m_id;
}

const std::string &DiffFile::get_id() const
{
    return m_id;
}

void DiffFile::set_path(const std::string &path)
{
    m_path = path;
}

std::string &DiffFile::get_path()
{
    return m_path;
}

const std::string &DiffFile::get_path() const
{
    return m_path;
}

void DiffFile::set_size(uint64_t size)
{
    m_size = size;
}

uint64_t &DiffFile::get_size()
{
    return m_size;
}

uint64_t DiffFile::get_size() const
{
    return m_size;
}

} // namespace git

} // namespace repo

} // namespace esys
