/*!
 * \file esys/repo/gitmngr.h
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

#pragma once

#include "esys/repo/esysrepo_defs.h"
#include "esys/repo/gitbase.h"

#include <esys/log/user.h>

#include <vector>
#include <memory>

//<swig_inc/>

namespace esys
{

namespace repo
{

/*! \class GitMngr esys/repo/gitmngr.h "esys/repo/gitmgr.h"
 * \brief Git Manager
 *
 */
class ESYSREPO_API GitMngr : public log::User
{
public:
    typedef std::shared_ptr<GitBase>(*NewPtrFct)();

    //! Constructor
    GitMngr();

    //! Destructor
    virtual ~GitMngr();

    static void set_new_ptr(NewPtrFct new_ptr_fct);
    static NewPtrFct get_new_ptr();
    static std::shared_ptr<GitBase> new_ptr();
    
protected:
    //!< \cond DOXY_IMPL
    static NewPtrFct m_new_ptr_fct;
    //!< \endcond
};

} // namespace repo

} // namespace esys
