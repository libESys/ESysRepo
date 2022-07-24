/*!
 * \file esys/repo/exe/cmdsync.h
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

#include "esys/repo/gitbase.h"

#include <string>
#include <vector>
#include <memory>

//<swig_inc/>

namespace esys::repo::exe
{

class ESYSREPO_API CmdSync : public Cmd
{
public:
    CmdSync();
    ~CmdSync() override;

    //! Set if the manifest is known to be a git super project
    /*!
     *  \param[in] git_super_project if true, the "manifest" to use is a git super project
     */
    void set_force(bool force);
    bool get_force() const;

    void set_branch(const std::string &branch);
    const std::string &get_branch() const;

    void set_alt_address(bool alt_address);
    bool get_alt_address() const;

    int sync_manifest();

protected:
    //!< \cond DOXY_IMPL
    Result impl_run() override;

private:
    bool m_force = false;
    std::string m_branch;
    bool m_alt_address = false;
    //!< \endcond
};

} // namespace esys::repo::exe
