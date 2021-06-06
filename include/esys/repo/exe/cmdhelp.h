/*!
 * \file esys/repo/exe/cmdhelp.h
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
#include "esys/repo/exe/cmd.h"

namespace esys
{

namespace repo
{

namespace exe
{

class ESYSREPO_API CmdHelp : public Cmd
{
public:
    CmdHelp();
    virtual ~CmdHelp();

protected:
    //!< \cond DOXY_IMPL
    int impl_run() override;

    //!< \endcond
};

} // namespace exe

} // namespace repo

} // namespace esys
