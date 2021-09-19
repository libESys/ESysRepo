/*!
 * \file esys/repo/manifest/taskbase_mannifest.cpp
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
#include "esys/repo/manifest/taskbase.h"

namespace esys
{

namespace repo
{

namespace manifest
{

TaskBase::TaskBase()
{
}

TaskBase::~TaskBase()
{
}

void TaskBase::set_git(std::shared_ptr<GitBase> git)
{
    m_git = git;

    if (git != nullptr) git->set_progress_callback(&m_progress_callback);
}

std::shared_ptr<GitBase> TaskBase::get_git()
{
    return m_git;
}

const std::shared_ptr<GitBase> TaskBase::get_git() const
{
    return m_git;
}

void TaskBase::set_config_folder(std::shared_ptr<ConfigFolder> config_folder)
{
    m_config_folder = config_folder;
}

std::shared_ptr<ConfigFolder> TaskBase::get_config_folder()
{
    return m_config_folder;
}

const std::shared_ptr<ConfigFolder> TaskBase::get_config_folder() const
{
    return m_config_folder;
}

void TaskBase::set_repo(std::shared_ptr<Repository> repo)
{
    m_repo = repo;
}

std::shared_ptr<Repository> TaskBase::get_repo()
{
    return m_repo;
}

void TaskBase::set_result(int result)
{
    m_result = result;
}

int TaskBase::get_result() const
{
    return m_result;
}

void TaskBase::clear_errors()
{
    m_errors.clear();
}

void TaskBase::add_errors(const std::string &error)
{
    m_errors.push_back(error);
}

std::vector<std::string> &TaskBase::get_errors()
{
    return m_errors;
}

const std::vector<std::string> &TaskBase::get_errors() const
{
    return m_errors;
}

void TaskBase::set_id(std::size_t id)
{
    m_id = id;
}

std::size_t TaskBase::get_id() const
{
    return m_id;
}

void TaskBase::git_progress_notif(const git::Progress &progress)
{
    std::lock_guard lock(m_progress_mutex);

    if (m_progress.get_started()) set_running(true);
    if (m_progress.get_done()) set_running(false);

    m_progress = progress;
}

void TaskBase::get_progress(git::Progress &progress)
{
    std::lock_guard lock(m_progress_mutex);

    progress = m_progress;
}

void TaskBase::set_running(bool running)
{
    m_running = running;
}

bool TaskBase::get_running()
{
    std::lock_guard lock(m_progress_mutex);

    return m_running;
}

} // namespace manifest

} // namespace repo

} // namespace esys
