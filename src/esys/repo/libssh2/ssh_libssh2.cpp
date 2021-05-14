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

namespace esys
{

namespace repo
{

namespace libssh2
{

SSH::SSH()
    : SSHBase()
{
    m_impl = std::make_unique<SSHImpl>();
}

SSH::~SSH()
{
}

bool SSH::is_agent_present()
{
    if (_get_agent_present() == AgentPresent::NOT_CHECKED)
    {
        bool present = m_impl->is_agent_present();
        if (present) _set_agent_present(AgentPresent::PRESENT);
        else
            _set_agent_present(AgentPresent::NOT_PRESENT);
    }
    return (_get_agent_present() == AgentPresent::PRESENT);
}

} // namespace libssh2

} // namespace repo

} // namespace esys
