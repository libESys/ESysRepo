/*!
 * \file esys/repo/exe/cmdversion.h
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

namespace esys::repo::exe
{

class ESYSREPO_API CmdVersion : public Cmd
{
public:
    static const int NAME_SIZE = 15;

    CmdVersion();
    ~CmdVersion() override;

    void set_version(const std::string &version);
    const std::string &get_version() const;

protected:
    //!< \cond DOXY_IMPL
    Result impl_run() override;

private:
    std::string m_version;
    //!< \endcond
};

} // namespace esys::repo::exe
