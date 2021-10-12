/*!
 * \file esys/repo/cli/cmdinit_cli.cpp
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
#include "esys/repo/cli/cmdinit.h"

#include <msword2md/cpp/string.h>

#include <termcolor/termcolor.hpp>

#include <boost/filesystem.hpp>

#include <vector>

namespace esys::repo::cli
{

#include "esys/repo/cli/cmdinit_doc.cpp"

CmdInit::CmdInit(AppBase *app)
    : BaseType(app, "init")
{
}

CmdInit::~CmdInit() = default;

std::shared_ptr<po::options_description> CmdInit::get_desc()
{
    auto desc = Cmd::get_desc();
    if (desc != nullptr) return desc;

    desc = std::make_shared<po::options_description>("Init options");
    // clang-format off
    desc->add_options()
        ("help,h", "produce help message")
        ("manifest-url,u", po::value<std::string>()->required(), "manifest repository location")
        ("manifest-branch,b", po::value<std::string>(), "manifest branch or revision")
        ("manifest-name,m", po::value<std::string>(), "initial manifest file")
        ("google,g", po::value<bool>()->default_value(false)->implicit_value(true), "google manifest")
        ("git-super,s", po::value<bool>()->default_value(false)->implicit_value(true), "git super project")
        ;
    // clang-format on
    Cmd::set_desc(desc);
    return desc;
}

int CmdInit::configure_cmd(CmdType &cmd)
{
    get_cmd().set_url(get_vm()["manifest-url"].as<std::string>());
    if (get_vm().count("manifest-branch")) get_cmd().set_branch(get_vm()["manifest-branch"].as<std::string>());
    if (get_vm().count("manifest-name")) get_cmd().set_manifest_name(get_vm()["manifest-name"].as<std::string>());
    if (get_vm().count("google")) get_cmd().set_google_manifest(get_vm()["google"].as<bool>());
    if (get_vm().count("git-super")) get_cmd().set_google_manifest(get_vm()["git-super"].as<bool>());

    /*if (!get_folder().empty() && !get_workspace().empty())
    {
        error("--folder and --workspace can't be specified at the same time");
        return -1;
    }
    else if (!get_folder().empty() || !get_workspace().empty())
    {
        boost::filesystem::path path;
        if (!get_folder().empty())
            path = get_folder();
        else
            path = get_workspace();
        path = boost::filesystem::absolute(path).normalize().make_preferred();
        get_cmd().set_workspace_path(path.string());
    }
    else
        get_cmd().set_workspace_path(boost::filesystem::current_path().normalize().make_preferred().string()); */
    get_cmd().set_google_manifest(get_vm()["google"].as<bool>());

    return 0;
}

int CmdInit::print_help(std::ostream &os)
{
    os << cmdinit_doc_strings;
    return 0;
}

} // namespace esys::repo::cli
