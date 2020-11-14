/*!
 * \file esys/repo/configfileimpl.h
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
#include "esys/repo/configfile.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace esys
{

namespace repo
{

class ESYSREPO_API ConfigFileImpl
{
public:
    ConfigFileImpl(ConfigFile *self);
    virtual ~ConfigFileImpl();

    int open(const std::string &path = "");
    int write(const std::string &path = "");

    ConfigFile *self();
    const ConfigFile *self() const;

protected:
    ConfigFile *m_self = nullptr;
};

} // namespace repo

} // namespace esys
