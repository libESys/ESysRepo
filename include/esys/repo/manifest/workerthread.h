/*!
 * \file esys/repo/manifest/workerthread.h
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

#include <thread>

namespace esys
{

namespace repo
{

namespace manifest
{

/*! \class WorkerThread esys/repo/manifest/workerthread.h "esys/repo/manifest/workerthread.h"
 * \brief
 */
class ESYSREPO_API WorkerThread
{
public:
    explicit WorkerThread(int id);

    void set_id(int id);
    int get_id() const;

private:
    int m_id = -1;
};

} // namespace manifest

} // namespace repo

} // namespace esys
