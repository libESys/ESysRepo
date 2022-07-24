/*!
 * \file esys/repo/exe/cmdstatus.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2022 Michel Gillet
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
#include "esys/repo/exe/cmd.h"
#include "esys/repo/git/repostatus.h"
#include "esys/repo/git/branches.h"

#include <memory>
#include <vector>

namespace esys::repo::exe
{

/*! \class CmdStatus esys/repo/exe/cmdstatus.h "esys/repo/exe/cmdstatus.h"
 * \brief Satus command
 */
class ESYSREPO_API CmdStatus : public Cmd
{
public:
    //! Default constructor
    CmdStatus();

    //! Destructor
    ~CmdStatus() override;

    void set_quiet(bool quiet);
    bool get_quiet() const;

    int open_repo(std::shared_ptr<manifest::Repository> repo);
    void print_repo(std::shared_ptr<manifest::Repository> repo);

    void set_start_print_branch(std::size_t start_print_branch);
    std::size_t get_start_print_branch() const;

    void print(std::ostream &os, std::shared_ptr<git::FileStatus> file_status);

    std::string get_file_status_header(std::shared_ptr<git::FileStatus> file_status);

    int process_sub_args_to_find_parent_path();

    void set_show_file_permission(bool show_file_permission);
    bool get_show_file_permission() const;

protected:
    //!< \cond DOXY_IMPL
    Result impl_run() override;

private:
    bool m_quiet = false;
    std::string m_rel_repo_path;
    std::string m_repo_path;
    std::shared_ptr<git::CommitHash> m_last_commit;
    std::size_t m_start_print_branch = 50;
    std::shared_ptr<git::RepoStatus> m_repo_status;
    git::Branches m_branches;
    std::map<std::string, int> m_map_repo_path_to_show;
    bool m_show_file_permission = true;
    //!< \endcond
};

} // namespace esys::repo::exe
