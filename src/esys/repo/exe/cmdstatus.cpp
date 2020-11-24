/*!
 * \file esys/repo/exe/cmdstatus.cpp
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
#include "esys/repo/exe/cmdstatus.h"
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

CmdStatus::CmdStatus()
    : Cmd("Status")
{
}

CmdStatus::~CmdStatus()
{
}

void CmdStatus::set_quiet(bool quiet)
{
    m_quiet = quiet;
}

bool CmdStatus::get_quiet() const
{
    return m_quiet;
}

int CmdStatus::impl_run()
{
    int result;

    if (get_quiet()) warn("The option --quiet is not implemented yet");

    result = process_sub_args_to_find_parent_path();
    if (result < 0)
    {
        error("No ESysRepo folder found");
        return -1;
    }

    result = load_manifest();
    if (result < 0) return result;

    result = process_sub_args_as_git_repo_paths();
    if (result < 0) return result;

    std::map<std::string, int> map_input_repo_paths;

    if (get_input_git_repo_paths().size() != 0)
    {
        for (auto &path : get_input_git_repo_paths())
        {
            auto repo = get_manifest()->find_repo_by_path(path);
            if (repo != nullptr) map_input_repo_paths[path] = 1;
        }
    }

    for (auto location : get_manifest()->get_locations())
    {
        for (auto repo : location->get_repos())
        {
            if (map_input_repo_paths.size() != 0)
            {
                if (map_input_repo_paths.find(repo->get_path()) == map_input_repo_paths.end()) continue;
            }
            result = open_repo(repo);
            if (result < 0) continue;
            print_repo(repo);
        }
    }

    return result;
}

int CmdStatus::open_repo(std::shared_ptr<manifest::Repository> repo)
{
    GitHelper git_helper(get_git(), get_logger_if());
    git_helper.set_auto_close();

    boost::filesystem::path rel_repo_path;
    boost::filesystem::path repo_path = get_config_folder()->get_parent_path();
    repo_path /= repo->get_path();
    repo_path = boost::filesystem::absolute(repo_path).normalize().make_preferred();
    rel_repo_path = boost::filesystem::relative(repo_path);

    m_rel_repo_path = rel_repo_path.string();
    m_repo_path = repo_path.string();

    int result = git_helper.open(repo_path.string(), log::Level::DEBUG);
    if (result < 0) return result;

    m_repo_status = std::make_shared<git::RepoStatus>();

    result = git_helper.get_status(*m_repo_status, log::Level::DEBUG);
    if (result < 0) return result;

    m_repo_status->sort_file_status();

    m_branches.clear();

    result = git_helper.get_branches(m_branches, git::BranchType::LOCAL, log::Level::DEBUG);
    if (result < 0) return result;

    GitHelper::sort_branches(m_branches);

    return git_helper.close(log::Level::DEBUG);
}

void CmdStatus::print_repo(std::shared_ptr<manifest::Repository> repo)
{
    std::ostringstream oss;
    std::string first_part;
    std::string cur_branch;

    if (m_branches.size() != 0)
    {
        if (m_branches[0].get_is_head()) cur_branch = m_branches[0].get_name();
    }

    if (m_repo_status->get_file_status().size() == 0)
    {
        std::string rev = get_manifest()->get_repo_revision(repo);

        auto index = rev.find("refs/heads/");
        if (index != rev.npos) rev = rev.substr(index + std::strlen("refs/heads/"));

        if (rev == cur_branch) return;
    }

    first_part = "Repository : " + repo->get_path();
    oss << std::setw(get_start_print_branch()) << std::setfill(' ') << std::left << first_part;

    if (!cur_branch.empty()) oss << cur_branch;

    for (auto file_status : m_repo_status->get_file_status())
    {
        oss << std::endl;
        print(oss, file_status);
    }

    info(oss.str());
}

void CmdStatus::print(std::ostream &os, std::shared_ptr<git::FileStatus> file_status)
{
    os << get_file_status_header(file_status);
    os << "     ";
    os << file_status->get_old_name();
}

std::string CmdStatus::get_file_status_header(std::shared_ptr<git::FileStatus> file_status)
{
    return "--";
}

void CmdStatus::set_start_print_branch(std::size_t start_print_branch)
{
    m_start_print_branch = start_print_branch;
}

std::size_t CmdStatus::get_start_print_branch() const
{
    return m_start_print_branch;
}

int CmdStatus::process_sub_args_to_find_parent_path()
{
    if (!get_parent_path().empty()) return 0;

    if (get_sub_args().size() == 0)
    {
        std::string parent_path = Cmd::find_parent_path();
        if (parent_path.empty()) return -1;

        set_parent_path(parent_path);
        return 0;
    }

    std::string parent_path;

    for (auto &path : get_sub_args())
    {
        //if (!boost::filesystem::exists(path)) continue;
        parent_path = Cmd::find_parent_path(path);
        if (!parent_path.empty())
        {
            set_parent_path(parent_path);
            return 0;
        }
    }

    parent_path = Cmd::find_parent_path();
    if (parent_path.empty()) return -1;

    set_parent_path(parent_path);
    return 0;
}

} // namespace exe

} // namespace repo

} // namespace esys
