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
#include "esys/repo/manifest/sync.h"

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

int CmdSync::sync_manifest()
{
    manifest::Sync sync;

    if (get_config_folder() == nullptr) return -1;

    sync.set_config_folder(get_config_folder());
    sync.set_git(get_git());
    sync.set_logger_if(get_logger_if());

    return sync.run();
}

int CmdSync::impl_run()
{
    int result;

    if (get_force()) warn("Option --force-sync is not implemented yet");

    result = open_esysrepo_folder();
    if (result < 0) return result;

    result = sync_manifest();
    if (result < 0) return result;

    result = load_manifest();
    if (result < 0) return result;

    manifest::SyncRepos sync_repos;

    if (get_sub_args().size() != 0)
        sync_repos.set_folders_to_sync(get_sub_args());
    else if (get_groups().size() != 0)
    {
        std::vector<std::string> repos;

        for (auto &group : get_groups())
        {
            auto group_ptr = get_manifest()->get_groups().find_group_by_name(group);
            if (group_ptr == nullptr)
            {
                //! \TODO 
                continue;
            }
            for (auto repo : group_ptr->get_repos())
            {
                repos.push_back(repo->get_path());
            }
        }

        sync_repos.set_folders_to_sync(repos);
    }

    if (get_debug()) sync_repos.set_log_level(log::Level::DEBUG);

    sync_repos.set_job_count(get_job_count());
    sync_repos.set_logger_if(get_logger_if());
    sync_repos.set_config_folder(get_config_folder());
    sync_repos.set_git(get_git());
    sync_repos.set_manifest(get_manifest());

    if (get_git()->is_ssh_agent_running()) info("SSH agent detected");

    result = sync_repos.run();
    if (result < 0) return result;
    return 0;
}

} // namespace exe

} // namespace repo

} // namespace esys
