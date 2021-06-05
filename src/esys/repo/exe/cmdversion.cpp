/*!
 * \file esys/repo/exe/cmdversion.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/exe/cmdversion.h"
#include "esys/repo/version.h"
#include "esys/repo/libgit2/git.h"

#include <sstream>
#include <iomanip>

namespace esys
{

namespace repo
{

namespace exe
{

CmdVersion::CmdVersion()
    : Cmd("Version")
{
}

CmdVersion::~CmdVersion()
{
}

void CmdVersion::set_version(const std::string &version)
{
    m_version = version;
}

const std::string &CmdVersion::get_version() const
{
    return m_version;
}

int CmdVersion::impl_run()
{
    std::ostringstream oss;

    oss << "Version ..." << std::endl;
    oss << std::setw(15) << std::left << "ESysRepo ";
    oss << get_version() << std::endl;

    oss << std::setw(15) << std::left << "ESysRepo lib" << ESYSREPO_VERSION_NUM_DOT_STRING << std::endl;

    oss << std::setw(15) << std::left << esys::repo::libgit2::Git::s_get_lib_name();
    oss << esys::repo::libgit2::Git::s_get_version() << std::endl;

    oss << std::setw(15) << std::left << esys::repo::libgit2::Git::s_get_ssh_lib_name();
    oss << esys::repo::libgit2::Git::s_get_ssh_version();

    info(oss.str());
    info("Version done.");
    return 0;
}

} // namespace exe

} // namespace repo

} // namespace esys