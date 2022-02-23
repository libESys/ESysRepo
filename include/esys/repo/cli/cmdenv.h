/*!
 * \file esys/repo/cli/cmdenv.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2022 Michel Gillet
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
#include "esys/repo/exe/cmdenv.h"

namespace esys::repo::cli
{

class ESYSREPO_API CmdEnv : public Cmd_t<exe::CmdEnv>
{
public:
    typedef Cmd_t<exe::CmdEnv> BaseType;

    explicit CmdEnv(AppBase *app = nullptr);
    ~CmdEnv() override;

    int configure_cmd(CmdType &cmd) override;
    std::shared_ptr<po::options_description> get_desc() override;

    int print_help(std::ostream &os) override;

protected:
};

} // namespace esys::repo::cli
