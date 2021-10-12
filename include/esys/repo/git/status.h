/*!
 * \file esys/repo/git/status.h
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
#include "esys/repo/git/statustype.h"
#include "esys/repo/git/statussubtype.h"
#include "esys/repo/git/diffdelta.h"

#include <string>

//<swig_inc/>

namespace esys
{

namespace repo
{

namespace git
{

/*! \class Status esys/repo/git/status.h "esys/repo/git/status.h"
 * \brief Status information about a file in a git repo
 */
class ESYSREPO_API Status
{
public:
    //! Default constructor
    Status();

    //! Destructor
    virtual ~Status();

    void set_type(StatusType type);
    StatusType get_type() const;
    StatusType &get_type();

    void set_sub_type(StatusSubType sub_type);
    StatusSubType get_sub_type() const;
    StatusSubType &get_sub_type();

    DiffDelta &get_diff_delta();
    const DiffDelta &get_diff_delta() const;

private:
    //!< \cond DOXY_IMPL
    StatusType m_type = StatusType::NOT_SET;
    StatusSubType m_sub_type = StatusSubType::NOT_SET;
    DiffDelta m_diff_delta;
    //!< \endcond
};

} // namespace git

} // namespace repo

} // namespace esys
