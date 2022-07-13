/*!
 * \file esys/repo/grepo/folder.h
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

#include <memory>
#include <string>

//<swig_inc/>

namespace esys::repo::grepo
{

/*! \class Folder esys/repo/grepo/folder.h "esys/repo/grepo/folder.h"
 * \brief Read the Google repo tool folder structure
 */
//<swig>%rename(GRepoFolder) Folder;</swig>
class ESYSREPO_API Folder
{
public:
    //! Default constructor
    Folder(const std::string &folder_path = "");

    ~Folder();

    int open(const std::string &folder_path = "");

    void set_folder_path(const std::string &folder_path);
    const std::string &get_folder_path() const;

    //! Get the ESysRepo configuration stored in the git repo
    /*!
     * \return the ESysRepo configuration stored in the git repo
     */
    std::shared_ptr<Config> get_config() const;

    //! Set the ESysRepo configuration stored in the git repo
    /*!
     * \param[in] config the ESysRepo configuration stored in the git repo
     */
    void set_config(std::shared_ptr<Config> config);

    //! Get the ESysRepo configuration stored in the git repo and create one if not set
    /*!
     * \return the ESysRepo configuration stored in the git repo
     */
    std::shared_ptr<Config> get_or_new_config();

private:
    //!< \cond DOXY_IMPL
    std::string m_folder_path;
    std::shared_ptr<Config> m_config;
    //!< \endcond
};

} // namespace esys::repo::grepo
