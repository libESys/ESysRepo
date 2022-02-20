/*!
 * \file esys/repo/libssh2/sshimpl_libssh2.cpp
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
#include "esys/repo/libssh2/sshimpl.h"
#include "esys/repo/libssh2/ssh.h"

#include <sstream>

namespace esys::repo::libssh2
{

std::unique_ptr<SSHImpl::InitRelease> SSHImpl::s_init_release;

SSHImpl::SSHImpl(SSH *self)
    : m_self(self)
{
    if (s_init_release == nullptr) s_init_release = std::make_unique<SSHImpl::InitRelease>();
}

SSHImpl::~SSHImpl() = default;

bool SSHImpl::is_agent_present()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    LIBSSH2_SESSION *session = libssh2_session_init();
    LIBSSH2_AGENT *agent = libssh2_agent_init(session);

    int error = libssh2_agent_connect(agent);
    if (error != LIBSSH2_ERROR_NONE)
    {
        char *msg = nullptr;
        libssh2_session_last_error(session, &msg, nullptr, 0);

        std::ostringstream oss;
        oss << "agent error (" << error << ") : " << msg << std::endl;
        // self()->error(oss.str());
    }
    // else
    //    self()->debug(0, "SSH agent detected");

    libssh2_agent_disconnect(agent);
    libssh2_agent_free(agent);
    libssh2_session_free(session);

    return (error == LIBSSH2_ERROR_NONE);
}

SSH *SSHImpl::self()
{
    return m_self;
}

} // namespace esys::repo::libssh2
