/*!
 * \file esys/repo/exe/cmdlist.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2022 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/exe/cmdlist.h"
#include "esys/repo/manifest/repository.h"

#include <sstream>

namespace esys::repo::exe
{

CmdList::CmdList()
    : Cmd("List")
{
}

CmdList::~CmdList() = default;

void CmdList::set_fullpath(bool fullpath)
{
    m_fullpath = fullpath;
}

bool CmdList::get_fullpath() const
{
    return m_fullpath;
}

void CmdList::set_name_only(bool name_only)
{
    m_name_only = name_only;
}

bool CmdList::get_name_only() const
{
    return m_name_only;
}

void CmdList::set_path_only(bool path_only)
{
    m_path_only = path_only;
}

bool CmdList::get_path_only() const
{
    return m_path_only;
}

Result CmdList::impl_run()
{
    if (get_fullpath()) warn("Option --fullpath is not implemented yet.");
    if (get_name_only()) warn("Option --name-only is not implemented yet.");
    if (get_path_only()) warn("Option --path-only is not implemtented yet.");

    Result result = default_handling_folder_workspace();
    if (result.error()) return ESYSREPO_RESULT(result);

    result = open_esysrepo_folder();
    if (result.error()) return ESYSREPO_RESULT(result);

    result = load_manifest();

    std::ostringstream oss;

    oss << "path : name";

    for (auto location : get_manifest()->get_locations())
    {
        for (auto repo : location->get_repos())
        {
            print_info(oss, repo);
        }
    }

    info(oss.str());

    return ESYSREPO_RESULT(result);
}

void CmdList::print_info(std::ostream &os, std::shared_ptr<manifest::Repository> repo)
{
    os << std::endl << repo->get_path() << " : " << repo->get_name();
}

} // namespace esys::repo::exe
