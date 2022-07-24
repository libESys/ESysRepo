/*!
 * \file esys/repo/exe/cmdhelp.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2022 Michel Gillet
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

namespace esys::repo::exe
{

class ESYSREPO_API CmdHelp : public Cmd
{
public:
    CmdHelp();
    ~CmdHelp() override;

protected:
    //!< \cond DOXY_IMPL
    Result impl_run() override;

    //!< \endcond
};

} // namespace esys::repo::exe
