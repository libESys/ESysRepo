/*!
 * \file esys/repo/exe/cmdversion.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2021 Michel Gillet
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
#include "esys/repo/exe/cmd.h"

#include "esys/repo/gitbase.h"

#include <string>
#include <vector>
#include <memory>

namespace esys
{

namespace repo
{

namespace exe
{

class ESYSREPO_API CmdVersion : public Cmd
{
public:
    CmdVersion();
    virtual ~CmdVersion();

    void set_version(const std::string &version);
    const std::string &get_version() const;

protected:
    //!< \cond DOXY_IMPL
    int impl_run() override;

    std::string m_version;
    //!< \endcond
};

} // namespace exe

} // namespace repo

} // namespace esys
