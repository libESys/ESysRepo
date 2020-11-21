/*!
 * \file esys/repo/git/status_git.cpp
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
#include "esys/repo/git/status.h"

namespace esys
{

namespace repo
{

namespace git
{

Status::Status()
{
}

Status::~Status()
{
}

void Status::set_type(StatusType type)
{
    m_type = type;
}

StatusType Status::get_type() const
{
    return m_type;
}

StatusType &Status::get_type()
{
    return m_type;
}

void Status::set_sub_type(StatusSubType sub_type)
{
    m_sub_type = sub_type;
}

StatusSubType Status::get_sub_type() const
{
    return m_sub_type;
}

StatusSubType &Status::get_sub_type()
{
    return m_sub_type;
}

DiffDelta &Status::get_diff_delta()
{
    return m_diff_delta;
}

const DiffDelta &Status::get_diff_delta() const
{
    return m_diff_delta;
}

} // namespace git

} // namespace repo

} // namespace esys
