/*!
 * \file esys/repo/configfile.h
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
#include "esys/repo/config.h"

#include <string>
#include <memory>

namespace esys
{

namespace repo
{

class ESYSREPO_API ConfigFileImpl;

class ESYSREPO_API ConfigFile
{
public:
    ConfigFile();
    virtual ~ConfigFile();

    void set_path(const std::string &path);
    const std::string &get_path() const;

    void set_config(std::shared_ptr<Config> config);
    std::shared_ptr<Config> get_config();
    const std::shared_ptr<Config> get_config() const;

    int open(const std::string &path = "");
    int write(const std::string &path = "");

    ConfigFileImpl *get_impl();
    const ConfigFileImpl *get_impl() const;

protected:
    std::unique_ptr<ConfigFileImpl> m_impl;
    std::shared_ptr<Config> m_config;
    std::string m_path;
};

} // namespace repo

} // namespace esys
