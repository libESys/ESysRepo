/*!
 * \file esys/repo/cli/app.h
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
#include "esys/repo/cli/appbase.h"

#include "esys/repo/cli/cmdinit.h"
#include "esys/repo/cli/cmdsync.h"

namespace esys
{

namespace repo
{

namespace cli
{

class ESYSREPO_API App : public AppBase
{
public:
    App();
    ~App();

    CmdInit &get_cmd_init();
    CmdSync &get_cmd_sync();

protected:
    CmdInit m_cmd_init{this};
    CmdSync m_cmd_sync{this};
};

} // namespace cli

} // namespace repo

} // namespace esys
