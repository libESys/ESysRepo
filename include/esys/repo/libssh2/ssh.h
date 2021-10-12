/*!
 * \file esys/repo/libssh2/ssh.h
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
#include "esys/repo/sshbase.h"

#include <memory>

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
    virtual ~SSH();

    bool is_agent_present() override;

private:
    //!< \cond DOXY_IMPL
    std::unique_ptr<SSHImpl> m_impl;
    //!< \endcond
};

} // namespace libssh2

#ifdef ESYSREPO_USE_LIBSSH2
using namespace libssh2;
#endif

} // namespace repo

} // namespace esys
