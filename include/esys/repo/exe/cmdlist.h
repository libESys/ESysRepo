/*!
 * \file esys/repo/exe/cmdlist.h
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
#include "esys/repo/configfolder.h"
#include "esys/repo/gitbase.h"

#include <memory>
#include <ostream>

namespace esys
{

namespace repo
{

namespace exe
{

class ESYSREPO_API CmdList : public Cmd
{
public:
    CmdList();
    virtual ~CmdList();

    void set_fullpath(bool fullpath);
    bool get_fullpath() const;

    void set_name_only(bool name_only);
    bool get_name_only() const;

    void set_path_only(bool name_only);
    bool get_path_only() const;

    void print_info(std::ostream &os, std::shared_ptr<manifest::Repository> repo);

protected:
    int impl_run() override;

private:
    bool m_fullpath = false;
    bool m_name_only = false;
    bool m_path_only = false;
};

} // namespace exe

} // namespace repo

} // namespace esys
