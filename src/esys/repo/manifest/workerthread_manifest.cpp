/*!
 * \file esys/repo/manifest/workerthread_manifest.cpp
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
#include "esys/repo/manifest/workerthread.h"

namespace esys::repo::manifest
{

WorkerThread::WorkerThread(int id)
    : m_id(id)
{
}

void WorkerThread::set_id(int id)
{
    m_id = id;
}

int WorkerThread::get_id() const
{
    return m_id;
}

} // namespace esys::repo::manifest
