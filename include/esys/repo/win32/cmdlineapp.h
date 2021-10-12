/*!
 * \file esys/repo/win32/cmdlineapp.h
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

#pragma once

#include "esys/repo/esysrepo_defs.h"
#include "esys/repo/manifest/type.h"

#include <string>
#include <memory>

namespace esys
{

namespace repo
{

namespace win32
{

/*! \class CmdLineApp esys/repo/win32/cmdlineapp.h "esys/repo/win32/cmdlineapp.h"
 * \brief
 */
class ESYSREPO_API CmdLineApp
{
public:
    //! Default configuration
    CmdLineApp();

    //! Destructor
    ~CmdLineApp();

    int init();

    static CmdLineApp &get();

private:
    //!< \cond DOXY_IMPL
    static std::unique_ptr<CmdLineApp> s_cmd_line_app;
    //!< \endcond
};

} // namespace win32

#ifdef WIN32
using namespace win32;
#endif

} // namespace repo

} // namespace esys
