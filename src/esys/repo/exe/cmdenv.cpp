/*!
 * \file esys/repo/exe/cmdenv.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/exe/cmdenv.h"

#include <boost/process/environment.hpp>

#include <sstream>
#include <iomanip>

namespace esys::repo::exe
{

CmdEnv::CmdEnv()
    : Cmd("Env")
{
    set_print_cmd_name_by_base(false);
}

CmdEnv::~CmdEnv() = default;

Result CmdEnv::impl_run()
{
    std::ostringstream oss;

    print_cmd_name(oss);
    oss << std::endl;

    auto env = boost::this_process::environment();

    std::size_t max_name_size = 0;

    for (auto item : env)
    {
        std::string name = item.get_name();
        if (name.size() > max_name_size) max_name_size = name.size();
    }

    for (auto item : env)
    {
        oss << std::setw(max_name_size + 1) << std::left << item.get_name() << " = ";
        oss << item.to_string() << std::endl;
    }

    info(oss.str());
    return ESYSREPO_RESULT(ResultCode::OK);
}

} // namespace esys::repo::exe
