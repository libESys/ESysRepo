/*!
 * \file esys/repo/git/repostatus.h
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
#include "esys/repo/git/filestatus.h"

#include <string>
#include <memory>
#include <vector>
#include <map>

//<swig_inc/>

namespace esys
{

namespace repo
{

namespace git
{

/*! \class RepoStatus esys/repo/git/repostatus.h "esys/repo/git/repostatus.h"
 * \brief Status information about all files in a git repo
 */
class ESYSREPO_API RepoStatus
{
public:
    //! Default constructor
    RepoStatus();

    //! Destructor
    virtual ~RepoStatus();

    void add(std::shared_ptr<Status> status);

    std::vector<std::shared_ptr<Status>> &get_all();
    const std::vector<std::shared_ptr<Status>> &get_all() const;

    std::vector<std::shared_ptr<Status>> &get_current();
    const std::vector<std::shared_ptr<Status>> &get_current() const;

    std::vector<std::shared_ptr<Status>> &get_head_to_index();
    const std::vector<std::shared_ptr<Status>> &get_head_to_index() const;

    std::vector<std::shared_ptr<Status>> &get_index_to_work_dir();
    const std::vector<std::shared_ptr<Status>> &get_index_to_work_dir() const;

    std::vector<std::shared_ptr<Status>> &get_ignored();
    const std::vector<std::shared_ptr<Status>> &get_ignored() const;

    std::vector<std::shared_ptr<Status>> &get_conflicted();
    const std::vector<std::shared_ptr<Status>> &get_conflicted() const;

    std::vector<std::shared_ptr<FileStatus>> &get_file_status();
    const std::vector<std::shared_ptr<FileStatus>> &get_file_status() const;

    void sort_file_status();

    std::map<std::string, std::shared_ptr<FileStatus>> &get_map_file_status();
    const std::map<std::string, std::shared_ptr<FileStatus>> &get_map_file_status() const;

private:
    //!< \cond DOXY_IMPL
    std::vector<std::shared_ptr<Status>> m_all;               //!< All status information
    std::vector<std::shared_ptr<Status>> m_current;           //!< All files with current status
    std::vector<std::shared_ptr<Status>> m_head_to_index;     //!< All files with index status
    std::vector<std::shared_ptr<Status>> m_index_to_work_dir; //!< All files with working directory status
    std::vector<std::shared_ptr<Status>> m_ignored;           //!< All ignored files
    std::vector<std::shared_ptr<Status>> m_conflicted;        //!< All files with conflicts
    std::vector<std::shared_ptr<FileStatus>> m_file_status;
    std::map<std::string, std::shared_ptr<FileStatus>> m_map_file_status;
    //!< \endcond
};

} // namespace git

} // namespace repo

} // namespace esys
