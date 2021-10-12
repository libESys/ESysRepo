/*!
 * \file esys/repo/git/filestatus.h
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
#include "esys/repo/git/status.h"

#include <memory>

//<swig_inc/>

namespace esys
{

namespace repo
{

namespace git
{

/*! \class FileStatus esys/repo/git/filestatus.h "esys/repo/git/filestatus.h"
 * \brief Status information about one file
 */
class ESYSREPO_API FileStatus
{
public:
    FileStatus(const std::string &old_name = "");
    ~FileStatus();

    void set_old_name(const std::string &old_name);
    const std::string &get_old_name() const;

    void add(std::shared_ptr<Status> status);

    void set_head_to_index(std::shared_ptr<Status> head_to_index);
    std::shared_ptr<Status> get_head_to_index();

    void set_index_to_work_dir(std::shared_ptr<Status> index_to_work_dir);
    std::shared_ptr<Status> get_index_to_work_dir();

    std::vector<std::shared_ptr<Status>> &get_status();
    const std::vector<std::shared_ptr<Status>> &get_status() const;

private:
    //!< \cond DOXY_IMPL
    std::string m_old_name;
    std::shared_ptr<Status> m_head_to_index;
    std::shared_ptr<Status> m_index_to_work_dir;
    std::vector<std::shared_ptr<Status>> m_status;
    //!< \endcond
};

} // namespace git

} // namespace repo

} // namespace esys
