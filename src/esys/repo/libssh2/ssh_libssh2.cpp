/*!
 * \file esys/repo/libssh2/ssh_libssh2.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2021 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/libssh2/ssh.h"
#include "esys/repo/libssh2/sshimpl.h"

#include <boost/filesystem.hpp>

#include <sstream>
#include <cstdlib>

namespace esys::repo::libssh2
{

SSH::SSH()
    : SSHBase()
{
    m_impl = std::make_unique<SSHImpl>(this);
}

SSH::~SSH() = default;

bool SSH::is_agent_present()
{
    check_for_custom_agent();

    if (_get_agent_present() == AgentPresent::NOT_CHECKED)
    {
        bool present = m_impl->is_agent_present();
        if (present)
            _set_agent_present(AgentPresent::PRESENT);
        else
            _set_agent_present(AgentPresent::NOT_PRESENT);
    }
    return (_get_agent_present() == AgentPresent::PRESENT);
}

void SSH::check_for_custom_agent(bool force_check)
{
    static int s_run_count = 0;

    if (s_run_count > 0) return;

    ++s_run_count;

    bool do_check = true;
#ifndef ESYSREPO_SNAP_BUILD
    do_check = false;
#endif

    if (do_check) debug(0, "Snap detected");

    char *ssh_auth_sock_c = getenv("SSH_AUTH_SOCK");
    std::string ssh_auth_sock = ssh_auth_sock_c ? ssh_auth_sock_c : "";

    if (ssh_auth_sock.size() != 0)
    {
        std::ostringstream oss;

        oss << "SSH_AUTH_SOCK = '" << ssh_auth_sock << "'";
        debug(0, oss.str());
    }
    else
    {
        debug(0, "SSH_AUTH_SOCK is not set");
        return;
    }

    if (!do_check && !force_check)
    {
        std::ostringstream oss;

        oss << "Set set_agent_identity_path to '" << ssh_auth_sock << "'";
        debug(0, oss.str());
        set_agent_identity_path(ssh_auth_sock.c_str());
        return;
    }

    char *home_c = getenv("HOME");
    char *snap_real_home_c = getenv("SNAP_REAL_HOME");
    
    boost::filesystem::path home = home_c;
    boost::filesystem::path snap_real_home = snap_real_home_c;

    std::ostringstream oss;

    oss << "SNAP_REAL_HOME = '" << snap_real_home << "'";
    debug(0, oss.str());

    if (ssh_auth_sock.find(snap_real_home.string()) == 0)
    {
        debug(0, "Nothing to do.");
        return;
    }

    // SSH_AUTH_SOCK points to a file that can be accessed by a snap application
    boost::filesystem::path esysrepo_dir = snap_real_home;
    boost::filesystem::path new_ssh_auth_sock;
    esysrepo_dir /= "_esysrepo";
    new_ssh_auth_sock = esysrepo_dir / ssh_auth_sock;

    if (boost::filesystem::exists(new_ssh_auth_sock))
    {
        std::ostringstream oss;

        oss << "Set set_agent_identity_path to '" << new_ssh_auth_sock.string() << "'";
        debug(0, oss.str());

        set_agent_identity_path(new_ssh_auth_sock.string());
        return;
    }

    oss.str("");

    oss << "This application was installed from a snap package." << std::endl;
    oss << "So it can't access the /tmp folder. When using an ssh agent or" << std::endl;
    oss << "using agent forwarding, required files are written to the /tmp." << std::endl;
    oss << "Currently, the only way around this is to mount the /tmp folder" << std::endl;
    oss << "in your home folder." << std::endl;
    oss << std::endl;
    oss << "To mount the /tmp folder:" << std::endl;

    boost::filesystem::path path = esysrepo_dir / "tmp";
    boost::filesystem::path tmp_path = path;

    if (!boost::filesystem::exists(path))
    {
        boost::filesystem::create_directories(path);
    }

    path = snap_real_home / "bin";
    if (!boost::filesystem::exists(path))
    {
        boost::filesystem::create_directories(path);
    }

    path /= "esysrepo_mount_tmp.sh";

    oss << "sudo " << path.string() << std::endl;

    std::ofstream ofs(path.string().c_str(), std::ios_base::out | std::ios_base::trunc);

    ofs << "#!/usr/bin/env sh" << std::endl;
    ofs << std::endl;
    ofs << "# This file was generated by esysrepo, so don't modify it." << std::endl;
    ofs << std::endl;
    ofs << "sudo mount --bind /tmp " << tmp_path.string() << std::endl;
    ofs.close();

    boost::filesystem::permissions(path, boost::filesystem::owner_exe | boost::filesystem::owner_read
                                             | boost::filesystem::owner_write);
    warn(oss.str());
}

} // namespace esys::repo::libssh2
