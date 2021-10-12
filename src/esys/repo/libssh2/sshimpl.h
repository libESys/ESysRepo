/*!
 * \file esys/repo/libssh2/sshimpl.h
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

#include <libssh2.h>

#include <memory>
#include <mutex>

namespace esys
{

namespace repo
{

namespace libssh2
{

/*! \class SSHImpl esys/repo/libssh2/sshimpl.h "esys/repo/libssh2/sshimpl.h"
 * \brief
 */
class ESYSREPO_API SSHImpl
{
public:
    //! Default constructor
    SSHImpl();

    //! Destructor
    virtual ~SSHImpl();

    bool is_agent_present();

private:
    //!< \cond DOXY_IMPL

    class InitRelease
    {
    public:
        InitRelease()
        {
            m_result = libssh2_init(0);
            m_init = true;
        }

        int get_result()
        {
            return m_result;
        }

        ~InitRelease()
        {
            if (m_init) libssh2_exit();
        }

    private:
        bool m_init = false;
        int m_result = 0;
    };

    static std::unique_ptr<InitRelease> s_init_release;

    std::mutex m_mutex;
    //!< \endcond
};

} // namespace libssh2

} // namespace repo

} // namespace esys
