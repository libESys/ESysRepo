/*!
 * \file esys/repo/git/filestatus_git.cpp
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
#include "esys/repo/git/filestatus.h"

namespace esys::repo::git
{

FileStatus::FileStatus(const std::string &old_name)
    : m_old_name(old_name)
{
}

FileStatus::~FileStatus() = default;

void FileStatus::set_old_name(const std::string &old_name)
{
    m_old_name = old_name;
}

const std::string &FileStatus::get_old_name() const
{
    return m_old_name;
}

void FileStatus::add(std::shared_ptr<Status> status)
{
    m_status.push_back(status);

    if (status->get_type() == StatusType::INDEX)
        set_head_to_index(status);
    else if (status->get_type() == StatusType::WORKING_DIR)
        set_index_to_work_dir(status);
}

void FileStatus::set_head_to_index(std::shared_ptr<Status> head_to_index)
{
    m_head_to_index = head_to_index;
}

std::shared_ptr<Status> FileStatus::get_head_to_index()
{
    return m_head_to_index;
}

void FileStatus::set_index_to_work_dir(std::shared_ptr<Status> index_to_work_dir)
{
    m_index_to_work_dir = index_to_work_dir;
}

std::shared_ptr<Status> FileStatus::get_index_to_work_dir()
{
    return m_index_to_work_dir;
}

std::vector<std::shared_ptr<Status>> &FileStatus::get_status()
{
    return m_status;
}

const std::vector<std::shared_ptr<Status>> &FileStatus::get_status() const
{
    return m_status;
}

} // namespace esys::repo::git
