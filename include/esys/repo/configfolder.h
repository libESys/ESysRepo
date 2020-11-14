/*!
 * \file esys/repo/configfolder.h
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

#include <string>
#include <vector>
#include <memory>

namespace esys
{

namespace repo
{

class ESYSREPO_API ConfigFolder
{
public:
    ConfigFolder();
    virtual ~ConfigFolder();

    void set_parent_path(const std::string &path);
    const std::string &get_parent_path() const;

    int create(const std::string &parent_path = "");
    int open(const std::string &parent_path = "");
    int write(const std::string &parent_path = "");

    const std::string &get_path() const;
    const std::string &get_temp_path() const;
    const std::string &get_config_file_path() const;

    std::shared_ptr<Config> get_config();
    void set_config(std::shared_ptr<Config> config);

    std::shared_ptr<Config> get_or_new_config();

    int write_config_file();
    void populate_all_pathes();

protected:
    std::string m_parent_path;
    std::string m_path;
    std::string m_temp_path;
    std::string m_config_file_path;
    std::shared_ptr<Config> m_config;
    std::shared_ptr<ConfigFile> m_config_file;
};

} // namespace repo

} // namespace esys