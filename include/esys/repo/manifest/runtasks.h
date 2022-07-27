/*!
 * \file esys/repo/manifest/runtasks.h
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

#pragma once

#include "esys/repo/esysrepo_defs.h"
#include "esys/repo/queuemt.h"
#include "esys/repo/manifest/taskbase.h"
#include "esys/repo/manifest/workerthread.h"

#include <esys/log/user.h>

#include <string>
#include <memory>
#include <vector>
#include <thread>
#include <atomic>
#include <condition_variable>

namespace esys
{

namespace repo
{

namespace manifest
{

/*! \class RunTasks esys/repo/manifest/runtasks.h "esys/repo/manifest/runtasks.h"
 * \brief Execute a list of tasks
 */
class ESYSREPO_API RunTasks : public log::User
{
public:
    //! Default constructor
    RunTasks();

    //! Destructor
    ~RunTasks() override;

    //! Add a task to do
    /*!
     * \param[in] task the task
     */
    void add(std::shared_ptr<TaskBase> task);

    //! Set the job count
    /*!
     * \param[in] job_count the job count
     */
    void set_job_count(std::size_t job_count);

    //! Get the job count
    /*!
     * \return the job count
     */
    std::size_t get_job_count() const;

    //! Execute all tasks
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    Result run();

    std::size_t get_worker_thread_count();

    void worker_thread(std::shared_ptr<WorkerThread> work_thread);
    void cout_thread();
    void wait_done();

protected:
    //!< \cond DOXY_IMPL

    void remove(std::shared_ptr<WorkerThread> worker_thread);

    class RemoveWorkerThreadGuard
    {
    public:
        RemoveWorkerThreadGuard(RunTasks *run_tasks, std::shared_ptr<WorkerThread> worker_thread)
            : m_run_tasks(run_tasks)
            , m_work_thread(worker_thread)
        {
        }

        ~RemoveWorkerThreadGuard()
        {
            m_run_tasks->remove(m_work_thread);
        }

    private:
        RunTasks *m_run_tasks = nullptr;
        std::shared_ptr<WorkerThread> m_work_thread;
    };

private:
    std::atomic_bool m_done{false};
    std::condition_variable m_done_cond;
    std::mutex m_done_mutex;
    QueueMT<std::shared_ptr<TaskBase>> m_tasks;
    QueueMT<std::shared_ptr<TaskBase>> m_tasks_done;
    QueueMT<std::shared_ptr<TaskBase>> m_tasks_running;
    std::vector<std::thread> m_threads;
    QueueMT<std::shared_ptr<WorkerThread>> m_worker_threads;
    std::thread m_cout_thread;
    std::size_t m_job_count = 1;
    std::size_t m_cout_interval_ms = 500;
    std::size_t m_task_id = 0;
    std::size_t m_worker_thread_count = 0;
    //!< \endcond
};

} // namespace manifest

} // namespace repo

} // namespace esys
