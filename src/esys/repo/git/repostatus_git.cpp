/*!
 * \file esys/repo/git/repostatus.hpp
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
#include "esys/repo/git/repostatus.h"

#include <algorithm>

namespace esys::repo::git
{

RepoStatus::RepoStatus() = default;

RepoStatus::~RepoStatus() = default;

void RepoStatus::add(std::shared_ptr<Status> status)
{
    m_all.push_back(status);

    switch (status->get_type())
    {
        case StatusType::CURRENT: m_current.push_back(status); break;
        case StatusType::INDEX: m_head_to_index.push_back(status); break;
        case StatusType::WORKING_DIR: m_index_to_work_dir.push_back(status); break;
        case StatusType::IGNORED: m_ignored.push_back(status); break;
        case StatusType::CONFLICTED: m_conflicted.push_back(status); break;
        default:;
    }

    std::string old_file = status->get_diff_delta().get_old_file().get_path();
    if (old_file.empty()) return;

    auto it = m_map_file_status.find(old_file);
    std::shared_ptr<FileStatus> file_status;

    if (it == m_map_file_status.end())
    {
        file_status = std::make_shared<FileStatus>(old_file);
        m_map_file_status[old_file] = file_status;
        m_file_status.push_back(file_status);
    }
    else
        file_status = it->second;

    file_status->add(status);
}

std::vector<std::shared_ptr<Status>> &RepoStatus::get_all()
{
    return m_all;
}

const std::vector<std::shared_ptr<Status>> &RepoStatus::get_all() const
{
    return m_all;
}

std::vector<std::shared_ptr<Status>> &RepoStatus::get_current()
{
    return m_current;
}

const std::vector<std::shared_ptr<Status>> &RepoStatus::get_current() const
{
    return m_current;
}

std::vector<std::shared_ptr<Status>> &RepoStatus::get_head_to_index()
{
    return m_head_to_index;
}

const std::vector<std::shared_ptr<Status>> &RepoStatus::get_head_to_index() const
{
    return m_head_to_index;
}

std::vector<std::shared_ptr<Status>> &RepoStatus::get_index_to_work_dir()
{
    return m_index_to_work_dir;
}

const std::vector<std::shared_ptr<Status>> &RepoStatus::get_index_to_work_dir() const
{
    return m_index_to_work_dir;
}

std::vector<std::shared_ptr<Status>> &RepoStatus::get_ignored()
{
    return m_ignored;
}

const std::vector<std::shared_ptr<Status>> &RepoStatus::get_ignored() const
{
    return m_ignored;
}

std::vector<std::shared_ptr<Status>> &RepoStatus::get_conflicted()
{
    return m_conflicted;
}

const std::vector<std::shared_ptr<Status>> &RepoStatus::get_conflicted() const
{
    return m_conflicted;
}

std::vector<std::shared_ptr<FileStatus>> &RepoStatus::get_file_status()
{
    return m_file_status;
}

const std::vector<std::shared_ptr<FileStatus>> &RepoStatus::get_file_status() const
{
    return m_file_status;
}

void RepoStatus::sort_file_status()
{
    auto sort_by_name = [](const std::shared_ptr<FileStatus> f0, const std::shared_ptr<FileStatus> f1) -> bool {
        return f0->get_old_name() < f1->get_old_name();
    };

    std::sort(m_file_status.begin(), m_file_status.end(), sort_by_name);
}

std::map<std::string, std::shared_ptr<FileStatus>> &RepoStatus::get_map_file_status()
{
    return m_map_file_status;
}

const std::map<std::string, std::shared_ptr<FileStatus>> &RepoStatus::get_map_file_status() const
{
    return m_map_file_status;
}

} // namespace esys::repo::git
