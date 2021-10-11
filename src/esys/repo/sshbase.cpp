/*!
 * \file esys/repo/sshbase.cpp
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
#include "esys/repo/sshbase.h"

namespace esys::repo
{

SSHBase::SSHBase()
    : log::User()
{
}

SSHBase::~SSHBase() = default;

void SSHBase::_set_agent_present(AgentPresent agent_present)
{
    m_agent_present = agent_present;
}

SSHBase::AgentPresent SSHBase::_get_agent_present() const
{
    return m_agent_present;
}

} // namespace esys::repo
