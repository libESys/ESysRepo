/*!
 * \file esys/repo/gitbase.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 22020 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/gitbase.h"

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include <iostream>

namespace esys::repo
{

GitBase::GitBase()
    : log::User()
{
}

GitBase::~GitBase() = default;

int GitBase::reset_to_parent(int nth_parent)
{
    int result = is_open();

    if (result < 0) return result;

    git::CommitHash last_commit;
    git::CommitHash parent_commit;

    // Get the last commit in the manifest git repo
    result = get_last_commit(last_commit);
    if (result < 0) return result;

    // Get the its parent commit
    result = get_parent_commit(last_commit, parent_commit);
    if (result < 0) return result;

    // Reset the manifest git repo to the parent commit
    result = reset(parent_commit, git::ResetType::HARD);
    if (result < 0) return result;

    git::CommitHash new_last_commit;

    // Get the new last commit
    result = get_last_commit(new_last_commit);
    if (result < 0) return result;

    // The new last commit should be the parent commit
    if (parent_commit.get_hash() != new_last_commit.get_hash()) return -1;
    return 0;
}

bool GitBase::is_repo(const std::string &path)
{
    boost::filesystem::path git_path = path;

    git_path /= ".git";

    return boost::filesystem::exists(git_path);
}

void GitBase::set_id(std::size_t id)
{
    m_id = id;
}

std::size_t GitBase::get_id() const
{
    return m_id;
}

void GitBase::set_debug(bool debug)
{
    m_debug = debug;
}

bool GitBase::get_debug() const
{
    return m_debug;
}

int GitBase::handle_sideband_progress(const std::string &text)
{
    git::Progress progress;
    int result = decode_sideband_progress(text, progress);
    if (result == 0) set_progress(progress);

    if (get_progress_callback() != nullptr) get_progress_callback()->git_progress_notif(progress);

    return result;
}

int GitBase::handle_transfer_progress(const git::Progress &progress)
{
    set_progress(progress);

    if (get_progress_callback() != nullptr) get_progress_callback()->git_progress_notif(progress);

    return 0;
}

void GitBase::set_progress(const git::Progress &progress)
{
    std::lock_guard lock(m_progress_mutex);

    m_progress = progress;
}

void GitBase::get_progress(git::Progress &progress)
{
    std::lock_guard lock(m_progress_mutex);

    progress = m_progress;
}

void GitBase::set_progress_callback(ProgressCallbackBase *progress_callback)
{
    m_progress_callback = progress_callback;
}

ProgressCallbackBase *GitBase::get_progress_callback()
{
    return m_progress_callback;
}

int GitBase::decode_sideband_progress(const std::string &txt, git::Progress &progress)
{
    std::string txt_input = txt;

    std::replace(txt_input.begin(), txt_input.end(), '\r', '\n');
    boost::to_lower(txt_input);

    // std::cout << "'" << txt_input << "'" << std::endl;

    std::vector<std::string> lines;
    boost::split(lines, txt_input, [](char c) { return c == '\n'; });

    std::size_t percentage_idx = std::string::npos;
    progress.set_percentage(-1);
    bool percentage_error = false;
    progress.set_fetch_step(git::FetchStep::NOT_SET);

    for (auto &line : lines)
    {
        boost::trim(line);

        if (line.empty()) continue;

        progress.set_done(false);
        progress.set_percentage(-1);

        if (line.find("done") != line.npos) progress.set_done(true);
        percentage_idx = line.find("%");

        if (percentage_idx != line.npos)
        {
            std::string percentage_str = line.substr(0, percentage_idx);
            std::size_t i = percentage_str.rfind(' ');
            if (i != percentage_str.npos)
            {
                percentage_str = percentage_str.substr(i + 1);
                int result = 0;
                percentage_error = false;
                try
                {
                    result = std::stoi(percentage_str);
                }
                catch (std::invalid_argument &)
                {
                    percentage_error = true;
                    progress.set_percentage(-1);
                }
                catch (std::out_of_range &)
                {
                    percentage_error = true;
                    progress.set_percentage(-1);
                }
                if (percentage_error)
                    progress.set_percentage(-1);
                else
                    progress.set_percentage(result);
            }
        }

        if (line.find("enumerating") != line.npos)
        {
            progress.set_fetch_step(git::FetchStep::ENUMERATING);
        }
        else if (line.find("counting") != line.npos)
        {
            progress.set_fetch_step(git::FetchStep::COUNTING);
        }
        else if (line.find("compressing") != line.npos)
        {
            progress.set_fetch_step(git::FetchStep::COMPRESSING);
        }
        else if (line.find("total") != line.npos)
        {
            progress.set_fetch_step(git::FetchStep::TOTAL);
        }
    }
    return 0;
}

void GitBase::cmd_start()
{
    m_last_cmd_start_time = std::chrono::steady_clock::now();
    git::Progress progress;
    progress.set_started(true);
    set_progress(progress);

    if (get_progress_callback()) get_progress_callback()->git_progress_notif(progress);
}

void GitBase::cmd_end()
{
    m_last_cmd_end_time = std::chrono::steady_clock::now();
}

void GitBase::open_time()
{
    m_open_time = std::chrono::steady_clock::now();
}

void GitBase::close_time()
{
    m_close_time = std::chrono::steady_clock::now();
}

uint64_t GitBase::get_open_time()
{
    if (m_close_time < m_open_time) return 0;

    auto d_milli = std::chrono::duration_cast<std::chrono::milliseconds>(m_close_time - m_open_time).count();

    return static_cast<uint64_t>(d_milli);
}

uint64_t GitBase::get_last_cmd_elapsed_time()
{
    if (m_last_cmd_end_time < m_last_cmd_start_time) return 0;

    auto d_milli =
        std::chrono::duration_cast<std::chrono::milliseconds>(m_last_cmd_end_time - m_last_cmd_start_time).count();

    return static_cast<uint64_t>(d_milli);
}

} // namespace esys::repo
