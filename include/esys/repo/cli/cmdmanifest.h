/*!
 * \file esys/repo/cli/cmdmanifest.h
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
#include "esys/repo/cli/cmd_t.h"
#include "esys/repo/exe/cmdmanifest.h"

namespace esys
{

namespace repo
{

namespace cli
{

class ESYSREPO_API CmdManifest : public Cmd_t<exe::CmdManifest>
{
public:
    typedef Cmd_t<exe::CmdManifest> BaseType;

    CmdManifest(AppBase *app = nullptr);
    virtual ~CmdManifest();

    int configure_cmd(CmdType &cmd) override;
    std::shared_ptr<po::options_description> get_desc() override;

protected:
};

} // namespace cli

} // namespace repo

} // namespace esys
