/*!
 * \file esys/repo/cli/cmdinit.h
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
#include "esys/repo/exe/cmdinit.h"

namespace esys
{

namespace repo
{

namespace cli
{

class ESYSREPO_API CmdInit : public Cmd_t<exe::CmdInit>
{
public:
    typedef Cmd_t<exe::CmdInit> BaseType;

    CmdInit(AppBase *app = nullptr);
    ~CmdInit() override;

    int configure_cmd(CmdType &cmd) override;
    std::shared_ptr<po::options_description> get_desc() override;

    int print_help(std::ostream &os) override;

protected:
};

} // namespace cli

} // namespace repo

} // namespace esys
