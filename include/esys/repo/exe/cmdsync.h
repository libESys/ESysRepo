/*!
 * \file esys/repo/exe/cmdsync.h
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
#include "esys/repo/exe/cmd.h"

#include "esys/repo/gitbase.h"

#include <string>
#include <vector>
#include <memory>

namespace esys
{

namespace repo
{

namespace exe
{

class ESYSREPO_API CmdSync : public Cmd
{
public:
    CmdSync();
    virtual ~CmdSync();

    //! Set if the manifest is known to be a git super project
    /*!
     *  \param[in] git_super_project if true, the "manifest" to use is a git super project
     */
    void set_force(bool force);
    bool get_force() const;

protected:
    //!< \cond DOXY_IMPL
    int impl_run() override;

    bool m_force = false;
    //!< \endcond
};

} // namespace exe

} // namespace repo

} // namespace esys