/*!
 * \file esys/repo/loadfolder.h
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
#include "esys/repo/manifest.h"

#include <memory>
#include <string>

//<swig_inc/>

namespace esys::repo
{

/*! \class LoadFolder esys/repo/loadfolder.h "esys/repo/loadfolder.h"
 * \brief
 */
class ESYSREPO_API LoadFolder
{
public:
    LoadFolder(const std::string &folder_path = "");
    ~LoadFolder();

    void set_folder_path(const std::string &folder_path);
    const std::string &get_folder_path() const;

    int run(const std::string &folder_path = "");
    std::shared_ptr<Manifest> get_manifest();

    std::string find_repo_path_by_url(const std::string &url);
    std::shared_ptr<manifest::Repository> find_repo_by_url(const std::string &url);

private:
    void set_manifest(std::shared_ptr<Manifest> manifest);

    std::string m_folder_path;
    std::shared_ptr<Manifest> m_manifest;
};

} // namespace esys::repo
