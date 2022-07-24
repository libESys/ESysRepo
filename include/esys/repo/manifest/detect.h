/*!
 * \file esys/repo/manifest/detect.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2022 Michel Gillet
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
#include "esys/repo/configfolder.h"
#include "esys/repo/result.h"

#include <memory>
#include <string>

//<swig_inc/>

namespace esys::repo::manifest
{

/*! \class Detect esys/repo/manifest/detect.h "esys/repo/manifest/detect.h"
 * \brief Detect the type of manifest in a folder
 */
class ESYSREPO_API Detect
{
public:
    //! Default constructor
    Detect(const std::string &folder_path = "");

    //! Destructor
    ~Detect();

    void set_folder_path(const std::string &folder_path);
    const std::string &get_folder_path() const;

    Result detect(std::shared_ptr<Config> config = nullptr);

    void set_config(std::shared_ptr<Config> config);
    std::shared_ptr<Config> get_config();

    std::shared_ptr<ConfigFolder> get_config_folder();

private:
    //!< \cond DOXY_IMPL
    std::shared_ptr<Config> get_config_or_new();
    void set_config_folder(std::shared_ptr<ConfigFolder> config_folder);

    std::string m_folder_path;
    std::shared_ptr<Config> m_config;
    std::shared_ptr<ConfigFolder> m_config_folder;
    //!< \endcond
};

} // namespace esys::repo::manifest
