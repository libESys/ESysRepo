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

#include "esys/repo/cli/cmdenv.h"
#include "esys/repo/cli/cmdhelp.h"
#include "esys/repo/cli/cmdinfo.h"
#include "esys/repo/cli/cmdinit.h"
#include "esys/repo/cli/cmdlist.h"
#include "esys/repo/cli/cmdmanifest.h"
#include "esys/repo/cli/cmdstatus.h"
#include "esys/repo/cli/cmdsync.h"
#include "esys/repo/cli/cmdversion.h"

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
    ~App() override;

    void set_version(const std::string &version) override;

    CmdEnv &get_cmd_env();
    CmdHelp &get_cmd_help();
    CmdInfo &get_cmd_info();
    CmdInit &get_cmd_init();
    CmdList &get_cmd_list();
    CmdManifest &get_cmd_manifest();
    CmdStatus &get_cmd_status();
    CmdSync &get_cmd_sync();
    CmdVersion &get_cmd_version();

private:
    CmdEnv m_cmd_env{this};
    CmdHelp m_cmd_help{this};
    CmdInfo m_cmd_info{this};
    CmdInit m_cmd_init{this};
    CmdList m_cmd_list{this};
    CmdManifest m_cmd_manifest{this};
    CmdStatus m_cmd_status{this};
    CmdSync m_cmd_sync{this};
    CmdVersion m_cmd_version{this};
};

} // namespace cli

} // namespace repo

} // namespace esys
