/*!
 * \file esys/repo/sshbase.h
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

#pragma once

#include "esys/repo/esysrepo_defs.h"
#include <esys/log/user.h>

#include <mutex>
#include <string>

//<swig_inc/>

namespace esys
{

namespace repo
{

/*! \class SSHBase esys/repo/sshbase.h "esys/repo/sshbase.h"
 * \brief Base class for ssh client implementation
 */
class ESYSREPO_API SSHBase : public log::User
{
public:
    //! Default constructor
    SSHBase();

    //! Destructor
    ~SSHBase() override;

    //! Open a git repository for inspection
    /*!
     * \param[in] folder the folder where is the git repository
     * \return 0 if successful, < 0 otherwise
     */
    virtual bool is_agent_present() = 0;

protected:
    //!< \cond DOXY_IMPL
    enum class AgentPresent
    {
        NOT_CHECKED,
        PRESENT,
        NOT_PRESENT
    };

    void _set_agent_present(AgentPresent agent_present);
    AgentPresent _get_agent_present() const;

private:
    AgentPresent m_agent_present = AgentPresent::NOT_CHECKED;
    //!< \endcond
};

} // namespace repo

} // namespace esys
