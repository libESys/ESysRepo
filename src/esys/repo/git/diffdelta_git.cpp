/*!
 * \file esys/repo/git/diffdelta.cpp
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
#include "esys/repo/git/diffdelta.h"

namespace esys
{

namespace repo
{

namespace git
{

DiffDelta::DiffDelta()
{
}

DiffDelta::~DiffDelta()
{
}

void DiffDelta::set_type(DiffDeltaType type)
{
    m_type = type;
}

DiffDeltaType DiffDelta::get_type() const
{
    return m_type;
}

void DiffDelta::set_similatiry(std::size_t similarity)
{
    m_similarity = similarity;
}

std::size_t DiffDelta::get_similarity() const
{
    return m_similarity;
}

void DiffDelta::set_file_count(std::size_t file_count)
{
    m_file_count = file_count;
}

std::size_t DiffDelta::get_file_count() const
{
    return m_file_count;
}

DiffFile &DiffDelta::get_old_file()
{
    return m_old_file;
}

const DiffFile &DiffDelta::get_old_file() const
{
    return m_old_file;
}

DiffFile &DiffDelta::get_new_file()
{
    return m_new_file;
}

const DiffFile &DiffDelta::get_new_file() const
{
    return m_new_file;
}

} // namespace git

} // namespace repo

} // namespace esys
