/*!
 * \file esys/repo/cli/cmdsync_cli.cpp
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
#include "esys/repo/cli/cmdsync.h"

#include <msword2md/cpp/string.h>

#include <termcolor/termcolor.hpp>

#include <boost/filesystem.hpp>

#include <vector>

namespace esys
{

namespace repo
{

namespace cli
{

#include "esys/repo/cli/cmdsync_doc.cpp"

CmdSync::CmdSync(AppBase *app)
    : BaseType(app, "sync")
{
}

CmdSync::~CmdSync()
{
}

std::shared_ptr<po::options_description> CmdSync::get_desc()
{
    auto desc = Cmd::get_desc();
    if (desc != nullptr) return desc;

    desc = std::make_shared<po::options_description>("Sync options");
    // clang-format off
    desc->add_options()
        ("help,h", "produce help message")
        ("force-sync", po::value<bool>()->default_value(false)->implicit_value(true),
                        "overwrite an existing git directory if it needs to"
                        "point to a different object directory. WARNING: this"
                        "may cause loss of data")
        ("job,j", po::value<int>()->default_value(1), "projects to fetch simultaneously (default 1)")
        ("groups,g", po::value<std::string>(), "the groups to synchronize")
        ("branch,b", po::value<std::string>(), "the branch to synchronize across repos")
        ("alt,a", "use alternative address for git repos")
        ;
    // clang-format on
    Cmd::set_desc(desc);
    return desc;
}

int CmdSync::configure_cmd(CmdType &cmd)
{
    if (m_vm.count("job")) cmd.set_job_count(m_vm["job"].as<int>());
    cmd.set_sub_args(get_sub_args());
    if (m_vm.count("groups"))
    {
        std::vector<std::string> groups;

        int result = groups_str_to_groups(m_vm["groups"].as<std::string>(), groups);
        if (result < 0)
        {
            return -1;
        }
        cmd.set_groups(groups);
    }
    if (m_vm.count("branch")) cmd.set_branch(m_vm["branch"].as<std::string>());

    return 0;
}

int CmdSync::print_help(std::ostream &os)
{
    os << cmdsync_doc_strings;
    return 0;
}

} // namespace cli

} // namespace repo

} // namespace esys