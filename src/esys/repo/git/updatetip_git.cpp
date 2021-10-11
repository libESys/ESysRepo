/*!
 * \file esys/repo/git/updatetip_git.cpp
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
#include "esys/repo/git/updatetip.h"

namespace esys::repo::git
{

UpdateTip::UpdateTip() = default;

UpdateTip::~UpdateTip() = default;

void UpdateTip::set_type(UpdateTipType type)
{
    m_type = type;
}

UpdateTipType UpdateTip::get_type() const
{
    return m_type;
}

UpdateTipType &UpdateTip::get_type()
{
    return m_type;
}

void UpdateTip::set_ref_name(const std::string &ref_name)
{
    m_ref_name = ref_name;
}

const std::string &UpdateTip::get_ref_name() const
{
    return m_ref_name;
}

void UpdateTip::set_new_oid(const std::string &new_oid)
{
    m_new_oid = new_oid;
}

const std::string &UpdateTip::get_new_oid() const
{
    return m_new_oid;
}

void UpdateTip::set_old_oid(const std::string &old_oid)
{
    m_old_oid = old_oid;
}

const std::string &UpdateTip::get_old_oid() const
{
    return m_old_oid;
}

} // namespace esys::repo::git
