/*!
 * \file esys/repo/exe/cmdinfo.h
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
#include "esys/repo/git/commit.h"

#include <memory>
#include <ostream>
#include <vector>

namespace esys
{

namespace repo
{

namespace exe
{

/*! \class CmdInfo esys/repo/exe/cmdinfo.h "esys/repo/exe/cmdinfo.h"
 * \brief Info command
 */
class ESYSREPO_API CmdInfo : public Cmd
{
public:
    //! Default constructor
    CmdInfo();

    //! Destructor
    ~CmdInfo() override;

    void set_diff(bool diff);
    bool get_diff() const;

    void set_overview(bool overview);
    bool get_overview() const;

    void set_current_branch(bool current_branch);
    bool get_current_branch() const;

    void set_local_only(bool local_only);
    bool get_local_only() const;

    int open_repo(std::shared_ptr<manifest::Repository> repo);
    void print_repo(std::shared_ptr<manifest::Repository> repo);

protected:
    //!< \cond DOXY_IMPL
    int impl_run() override;

private:
    bool m_diff = false;
    bool m_overview = false;
    bool m_current_branch = false;
    bool m_local_only = false;
    git::Branches m_branches;
    std::string m_rel_repo_path;
    std::string m_repo_path;
    std::shared_ptr<git::Commit> m_last_commit;
    //!< \endcond
};

} // namespace exe

} // namespace repo

} // namespace esys
