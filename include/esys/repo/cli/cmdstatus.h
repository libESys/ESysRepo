/*!
 * \file esys/repo/cli/cmdstatus.h
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
#include "esys/repo/exe/cmdstatus.h"

namespace esys
{

namespace repo
{

namespace cli
{

class ESYSREPO_API CmdStatus : public Cmd_t<exe::CmdStatus>
{
public:
    typedef Cmd_t<exe::CmdStatus> BaseType;

    explicit CmdStatus(AppBase *app = nullptr);
    ~CmdStatus() override;

    int configure_cmd(CmdType &cmd) override;
    std::shared_ptr<po::options_description> get_desc() override;

    int print_help(std::ostream &os) override;

protected:
};

} // namespace cli

} // namespace repo

} // namespace esys
