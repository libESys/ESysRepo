/*!
 * \file esys/repo/gitmngr.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2021 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/gitmngr.h"
#include "esys/repo/libgit2/git.h"

namespace esys
{

namespace repo
{

GitMngr::NewPtrFct GitMngr::m_new_ptr_fct = nullptr;

GitMngr::GitMngr()
    : log::User()
{
}

GitMngr::~GitMngr()
{
}

void GitMngr::set_new_ptr(NewPtrFct new_ptr_fct)
{
    m_new_ptr_fct = new_ptr_fct;
}

GitMngr::NewPtrFct GitMngr::get_new_ptr()
{
    if (m_new_ptr_fct == nullptr) m_new_ptr_fct = libgit2::Git::new_ptr;

    return m_new_ptr_fct;
}

std::shared_ptr<GitBase> GitMngr::new_ptr()
{
    return (*get_new_ptr())();
}

} // namespace repo

} // namespace esys
