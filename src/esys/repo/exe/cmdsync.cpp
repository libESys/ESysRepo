/*!
 * \file esys/repo/exe/cmdsync.cpp
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
#include "esys/repo/exe/cmdsync.h"
#include "esys/repo/manifest/syncrepos.h"

namespace esys
{

namespace repo
{

namespace exe
{

CmdSync::CmdSync()
    : Cmd("Sync")
{
}

CmdSync::~CmdSync()
{
}

void CmdSync::set_force(bool force)
{
    m_force = force;
}

bool CmdSync::get_force() const
{
    return m_force;
}

int CmdSync::impl_run()
{
    int result;

    if (get_force()) warn("Option --force-sync is not implemented yet");

    result = load_manifest();
    if (result < 0) return result;

    manifest::SyncRepos clone_repos;

    if (get_debug()) clone_repos.set_log_level(log::Level::DEBUG);

    clone_repos.set_logger_if(get_logger_if());
    clone_repos.set_config_folder(get_config_folder());
    clone_repos.set_git(get_git());
    clone_repos.set_manifest(get_manifest());

    if (get_git()->is_ssh_agent_running()) get_logger_if()->info("SSH agent detected");

    result = clone_repos.run();
    if (result < 0) return result;
    return 0;
}

} // namespace exe

} // namespace repo

} // namespace esys