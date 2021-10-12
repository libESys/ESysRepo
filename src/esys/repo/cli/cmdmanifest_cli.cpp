/*!
 * \file esys/repo/cli/cmdmanifest_cli.cpp
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
#include "esys/repo/cli/cmdmanifest.h"

#include <msword2md/cpp/string.h>

#include <termcolor/termcolor.hpp>

#include <boost/filesystem.hpp>

#include <vector>

namespace esys::repo::cli
{

#include "esys/repo/cli/cmdmanifest_doc.cpp"

CmdManifest::CmdManifest(AppBase *app)
    : BaseType(app, "manifest")
{
}

CmdManifest::~CmdManifest() = default;

std::shared_ptr<po::options_description> CmdManifest::get_desc()
{
    auto desc = Cmd::get_desc();
    if (desc != nullptr) return desc;

    desc = std::make_shared<po::options_description>("List options");
    // clang-format off
    desc->add_options()
        ("help,h", "produce help message")
        ("revision-as-HEAD,r", "Save revisions as current HEAD")
        ("output-file,o", po::value<std::string>(), "File to save the manifest to")
        ;
    // clang-format on
    Cmd::set_desc(desc);
    return desc;
}

int CmdManifest::configure_cmd(CmdType &cmd)
{
    if (get_vm().count("revision-as-HEAD")) cmd.set_revision_as_head(true);
    if (get_vm().count("output-file")) cmd.set_output_file(get_vm()["output-file"].as<std::string>());

    return 0;
}

int CmdManifest::print_help(std::ostream &os)
{
    os << cmdmanifest_doc_strings;
    return 0;
}

} // namespace esys::repo::cli
