/*!
 * \file esys/repo/git/updatetip.h
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
#include "esys/repo/git/updatetiptype.h"

#include <string>

//<swig_inc/>

namespace esys
{

namespace repo
{

namespace git
{

/*! \class UpdateTip esys/repo/git/updatetip.h "esys/repo/git/updatetip.h"
 * \brief
 */
class ESYSREPO_API UpdateTip
{
public:
    //! Default constructor
    UpdateTip();

    //! Destructor
    virtual ~UpdateTip();

    void set_type(UpdateTipType type);
    UpdateTipType get_type() const;
    UpdateTipType &get_type();

    void set_ref_name(const std::string &ref_name);
    const std::string &get_ref_name() const;

    void set_new_oid(const std::string &new_oid);
    const std::string &get_new_oid() const;

    void set_old_oid(const std::string &old_oid);
    const std::string &get_old_oid() const;

protected:
    //!< \cond DOXY_IMPL
    UpdateTipType m_type = UpdateTipType::NOT_SET;
    std::string m_ref_name;
    std::string m_new_oid;
    std::string m_old_oid;
    //!< \endcond
};

} // namespace git

} // namespace repo

} // namespace esys
