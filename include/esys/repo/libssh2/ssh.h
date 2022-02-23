/*!
 * \file esys/repo/libssh2/ssh.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2021-2022 Michel Gillet
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
#include "esys/repo/sshbase.h"

#include <memory>
#include <string>

//<swig_inc/>

namespace esys
{

namespace repo
{

namespace libssh2
{

class ESYSREPO_API SSHImpl;

/*! \class SSH esys/repo/libssh2/ssh.h "esys/repo/libssh2/ssh.h"
 * \brief Base class for ssh client implementation
 */
class ESYSREPO_API SSH : public SSHBase
{
public:
    //! Default constructor
    SSH();

    //! Destructor
    ~SSH() override;

    bool is_agent_present() override;

    void check_for_custom_agent(bool force_check = false);

    void set_agent_identity_path(const std::string &agent_identity_path) override;
    const std::string &get_agent_identity_path() const override;

    static void set_dflt_agent_identity_path(const std::string &agent_identity_path);
    static const std::string &get_dflt_agent_identity_path();

private:
    //!< \cond DOXY_IMPL
    std::unique_ptr<SSHImpl> m_impl;
    static std::string s_dflt_agent_identity_path;
    //!< \endcond
};

} // namespace libssh2

#ifdef ESYSREPO_USE_LIBSSH2
using namespace libssh2;
#endif

} // namespace repo

} // namespace esys
