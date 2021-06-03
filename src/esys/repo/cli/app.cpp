/*!
 * \file esys/repo/cli/app.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/cli/app.h"

namespace esys
{

namespace repo
{

namespace cli
{

App::App()
    : AppBase()
{
}

App::~App()
{
}

CmdInit &App::get_cmd_init()
{
    return m_cmd_init;
}

} // namespace cli

} // namespace repo

} // namespace esys