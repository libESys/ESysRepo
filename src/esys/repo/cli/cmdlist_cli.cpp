/*!
 * \file esys/repo/cli/cmdlist_cli.cpp
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
#include "esys/repo/cli/cmdlist.h"

#include <msword2md/cpp/string.h>

#include <termcolor/termcolor.hpp>

#include <boost/filesystem.hpp>

#include <vector>

namespace esys::repo::cli
{

#include "esys/repo/cli/cmdlist_doc.cpp"

CmdList::CmdList(AppBase *app)
    : BaseType(app, "list")
{
}

CmdList::~CmdList() = default;

std::shared_ptr<po::options_description> CmdList::get_desc()
{
    auto desc = Cmd::get_desc();
    if (desc != nullptr) return desc;

    desc = std::make_shared<po::options_description>("List options");
    // clang-format off
    desc->add_options()
        ("help,h", "produce help message")
        ("fullpath,f", po::value<bool>()->default_value(false)->implicit_value(true),
                        "Display the full work tree path instead of the"
                        "relative path")
        ("name-only,n", po::value<bool>()->default_value(false)->implicit_value(true), "Display only the name of the repository")
        ("path-only,p", po::value<bool>()->default_value(false)->implicit_value(true), "Display only the path of the repository")
        ;
    // clang-format on
    Cmd::set_desc(desc);
    return desc;
}

int CmdList::configure_cmd(CmdType &cmd)
{
    if (m_vm["fullpath"].as<bool>()) cmd.set_fullpath(true);
    if (m_vm["name-only"].as<bool>()) cmd.set_name_only(true);
    if (m_vm["path-only"].as<bool>()) cmd.set_path_only(true);

    return 0;
}

int CmdList::print_help(std::ostream &os)
{
    os << cmdlist_doc_strings;
    return 0;
}

} // namespace esys::repo::cli
