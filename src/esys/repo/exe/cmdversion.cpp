/*!
 * \file esys/repo/exe/cmdversion.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/exe/cmdversion.h"
#include "esys/repo/version.h"
#include "esys/repo/libgit2/git.h"

#include <sstream>
#include <iomanip>

namespace esys::repo::exe
{

CmdVersion::CmdVersion()
    : Cmd("Version")
{
    set_print_cmd_name_by_base(false);
}

CmdVersion::~CmdVersion() = default;

void CmdVersion::set_version(const std::string &version)
{
    m_version = version;
}

const std::string &CmdVersion::get_version() const
{
    return m_version;
}

Result CmdVersion::impl_run()
{
    std::ostringstream oss;

    print_cmd_name(oss);
    oss << std::endl;
    oss << std::setw(NAME_SIZE) << std::left << "ESysRepo ";
    oss << get_version() << std::endl;

    oss << std::setw(NAME_SIZE) << std::left << "ESysRepo lib" << ESYSREPO_VERSION_NUM_DOT_STRING << std::endl;

    oss << std::setw(NAME_SIZE) << std::left << esys::repo::libgit2::Git::s_get_lib_name();
    oss << esys::repo::libgit2::Git::s_get_version() << std::endl;

    oss << std::setw(NAME_SIZE) << std::left << esys::repo::libgit2::Git::s_get_ssh_lib_name();
    oss << esys::repo::libgit2::Git::s_get_ssh_version();

    info(oss.str());
    return ESYSREPO_RESULT(ResultCode::OK);
}

} // namespace esys::repo::exe
