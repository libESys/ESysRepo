/*!
 * \file esys/repo/exe/cmdinfo.cpp
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
#include "esys/repo/exe/cmdinfo.h"
#include "esys/repo/manifest/repository.h"
#include "esys/repo/githelper.h"

#include <boost/filesystem.hpp>

#include <sstream>
#include <iomanip>

namespace esys
{

namespace repo
{

namespace exe
{

CmdInfo::CmdInfo()
    : Cmd("Info")
{
}

CmdInfo::~CmdInfo()
{
}

void CmdInfo::set_diff(bool diff)
{
    m_diff = diff;
}

bool CmdInfo::get_diff() const
{
    return m_diff;
}

void CmdInfo::set_overview(bool overview)
{
    m_overview = overview;
}

bool CmdInfo::get_overview() const
{
    return m_overview;
}

void CmdInfo::set_current_branch(bool current_branch)
{
    m_current_branch = current_branch;
}

bool CmdInfo::get_current_branch() const
{
    return m_current_branch;
}

void CmdInfo::set_local_only(bool local_only)
{
    m_local_only = local_only;
}

bool CmdInfo::get_local_only() const
{
    return m_local_only;
}

int CmdInfo::impl_run()
{
    int result = open_esysrepo_folder();
    if (result < 0) return result;

    result = load_manifest();
    if (result < 0) return result;

    for (auto location : get_manifest()->get_locations())
    {
        for (auto repo : location->get_repos())
        {
            result = open_repo(repo);
            if (result < 0) continue;
            print_repo(repo);
        }
    }

    return result;
}

int CmdInfo::open_repo(std::shared_ptr<manifest::Repository> repo)
{
    GitHelper git_helper(get_git(), get_logger_if());

    boost::filesystem::path rel_repo_path;
    boost::filesystem::path repo_path = get_config_folder()->get_workspace_path();
    repo_path /= repo->get_path();
    repo_path = boost::filesystem::absolute(repo_path).normalize().make_preferred();
    rel_repo_path = boost::filesystem::relative(repo_path);

    m_rel_repo_path = rel_repo_path.string();
    m_repo_path = repo_path.string();

    int result = git_helper.open(repo_path.string(), log::Level::DEBUG);
    if (result < 0) return result;

    m_last_commit = std::make_shared<git::Commit>();
    result = get_git()->get_last_commit(*m_last_commit);
    if (result < 0) m_last_commit.reset();

    m_branches.clear();

    result = git_helper.get_branches(m_branches, git::BranchType::LOCAL, log::Level::DEBUG);
    if (result < 0)
    {
        git_helper.close(log::Level::DEBUG);
        return result;
    }
    return git_helper.close(log::Level::DEBUG);
}

void CmdInfo::print_repo(std::shared_ptr<manifest::Repository> repo)
{
    std::ostringstream oss;
    std::shared_ptr<git::Branch> cur_branch = nullptr;

    for (auto branch : m_branches.get())
    {
        if (branch->get_is_head())
        {
            cur_branch = branch;
            break;
        }
    }
    std::string manifest_rev;

    oss << "Repo : " << repo->get_name() << std::endl;
    oss << "    Path           : " << m_rel_repo_path << std::endl;
    if (m_last_commit)
        oss << "    Cur rev.       : " << m_last_commit->get_hash() << std::endl;
    else
        oss << "    Cur rev.       : ???" << std::endl;
    if (cur_branch)
        oss << "    Cur branch     : " << cur_branch->get_name() << std::endl;
    else
        oss << "    Cur branch     : ???" << std::endl;
    oss << "    Manifest rev.  : " << get_manifest()->get_repo_revision(repo) << std::endl;
    oss << "    Local branches : " << m_branches.size();

    if (m_branches.size() == 0)
    {
        info(oss.str());
        return;
    }

    std::size_t idx = 0;
    for (auto branch : m_branches.get())
    {
        oss << std::endl << "        [" << idx << "] " << std::left << std::setw(20) << branch->get_name();
        oss << " -> " << branch->get_remote_branch();
        ++idx;
    }

    info(oss.str());
}

} // namespace exe

} // namespace repo

} // namespace esys
