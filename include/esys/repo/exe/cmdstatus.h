/*!
 * \file esys/repo/exe/cmdstatus.h
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
#include "esys/repo/exe/cmd.h"
#include "esys/repo/git/repostatus.h"
#include "esys/repo/git/branch.h"

#include <memory>
#include <vector>

namespace esys
{

namespace repo
{

namespace exe
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
    virtual ~CmdStatus();

    void set_quiet(bool quiet);
    bool get_quiet() const;

    int run() override;

    int open_repo(std::shared_ptr<manifest::Repository> repo);
    void print_repo(std::shared_ptr<manifest::Repository> repo);

    void set_start_print_branch(std::size_t start_print_branch);
    std::size_t get_start_print_branch() const;

    void print(std::ostream &os, std::shared_ptr<git::FileStatus> file_status);

    std::string get_file_status_header(std::shared_ptr<git::FileStatus> file_status);

protected:
    //!< \cond DOXY_IMPL
    bool m_quiet = false;
    std::string m_rel_repo_path;
    std::string m_repo_path;
    std::shared_ptr<git::Commit> m_last_commit;
    std::size_t m_start_print_branch = 50;
    std::shared_ptr<git::RepoStatus> m_repo_status;
    std::vector<git::Branch> m_branches;
    //!< \endcond
};

} // namespace exe

} // namespace repo

} // namespace esys
