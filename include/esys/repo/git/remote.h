/*!
 * \file esys/repo/git/remote.h
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

#include <string>

namespace esys
{

namespace repo
{

namespace git
{

class ESYSREPO_API Remote
{
public:
    Remote();
    virtual ~Remote();

    void set_name(const std::string &name);
    const std::string &get_name() const;

    void set_url(const std::string &url);
    const std::string &get_url() const;

protected:
    std::string m_name;
    std::string m_url;
};

} // namespace git

} // namespace repo

} // namespace esys
