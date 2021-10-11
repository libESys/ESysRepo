/*!
 * \file esys/repo/manifest/runtasks_manifest.cpp
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
#include "esys/repo/manifest/runtasks.h"

#include <esys/log/consolelockguard.h>

#include <chrono>
#include <sstream>
#include <iostream>

namespace esys::repo::manifest
{

RunTasks::RunTasks()
    : log::User()
{
}

RunTasks::~RunTasks()
{
    m_tasks.clear();
}

void RunTasks::add(std::shared_ptr<TaskBase> task)
{
    task->set_id(m_task_id);
    ++m_task_id;
    m_tasks.push_back(task);
}

void RunTasks::set_job_count(std::size_t job_count)
{
    m_job_count = job_count;
}

std::size_t RunTasks::get_job_count() const
{
    return m_job_count;
}

std::size_t RunTasks::get_worker_thread_count()
{
    m_worker_thread_count = get_job_count();

    if (m_tasks.size() < m_worker_thread_count) m_worker_thread_count = m_tasks.size();

    return m_worker_thread_count;
}

int RunTasks::run()
{
    if (m_tasks.size() == 0) return -1;
    if (static_cast<int>(get_job_count()) < 0) return -2;

    for (int idx = 0; idx < get_worker_thread_count(); ++idx)
    {
        std::shared_ptr<WorkerThread> worker = std::make_shared<WorkerThread>(idx);

        m_threads.push_back(std::thread(&RunTasks::worker_thread, this, worker));

        m_worker_threads.push_back(worker);
    }

    m_cout_thread = std::thread(&RunTasks::cout_thread, this);

    wait_done();

    for (auto &thread : m_threads)
    {
        if (thread.joinable()) thread.join();
    }

    if (m_cout_thread.joinable()) m_cout_thread.join();

    return 0;
}

void RunTasks::worker_thread(std::shared_ptr<WorkerThread> thread)
{
    RemoveWorkerThreadGuard remove_guard(this, thread);
    std::shared_ptr<TaskBase> task;

    int result = m_tasks.pop_front(task);
    while (result == 0)
    {
        m_tasks_running.push_back(task);

        try
        {
            task->run();
        }
        catch (const std::exception &e)
        {
            task->set_result(-1);
            task->add_errors(e.what());
        }
        catch (...)
        {
            task->set_result(-1);
            task->add_errors("Unknown exception.");
        }
        m_tasks_done.push_back(task);

        std::size_t id = task->get_id();
        auto remove_fct = [id](const std::shared_ptr<TaskBase> &task) { return (task->get_id() == id); };
        m_tasks_running.remove_if(remove_fct);

        result = m_tasks.pop_front(task);
    }
}

void RunTasks::cout_thread()
{
    std::ostringstream oss;
    auto print_fct = [&oss](const std::shared_ptr<TaskBase> &task) {
        git::Progress progress;

        if (task->get_running())
        {
            task->get_progress(progress);

            progress.print(oss, task->get_id());
        }
    };

    while (!m_done)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(m_cout_interval_ms));

        oss.str("");
        m_tasks_running.for_each(print_fct);
        {
            log::ConsoleLockGuard<log::User> lock(this);

            std::cout << "\r" << oss.str() << "\r";
        }
    }
}

void RunTasks::wait_done()
{
    std::unique_lock<std::mutex> lock{m_done_mutex};
    m_done_cond.wait(lock, [this] { return (m_done == true); });
}

void RunTasks::remove(std::shared_ptr<WorkerThread> rem_worker_thread)
{
    auto remove_fct = [rem_worker_thread](const std::shared_ptr<WorkerThread> &worker_thread) {
        return (rem_worker_thread->get_id() == worker_thread->get_id());
    };

    m_worker_threads.remove_if(remove_fct);
    m_worker_thread_count = m_worker_threads.size();
    if (m_worker_thread_count == 0) m_done = true;
    m_done_cond.notify_one();
}

} // namespace esys::repo::manifest
