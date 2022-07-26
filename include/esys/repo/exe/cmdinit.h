/*!
 * \file esys/repo/exe/cmdinit.h
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
#include "esys/repo/githelper.h"

#include <string>
#include <vector>
#include <memory>

//<swig_inc/>

//<swig>%shared_ptr(esys::repo::exe::CmdInit);</swig>

namespace esys::repo::exe
{

/*! \class CmdInit esys/repo/exe/cmdinit.h "esys/repo/exe/cmdinit.h"
 * \brief Init command
 */
class ESYSREPO_API CmdInit : public Cmd
{
public:
    //! Default destructor
    CmdInit();

    //! Destructor
    ~CmdInit() override;

    //! Set the url of the git repo with the manifest
    /*!
     *  \param[in] url the url of the git repo with the manifest
     */
    void set_url(const std::string &url);

    //! Get the url of the git repo with the manifest
    /*!
     *  \return the url of the git repo with the manifest
     */
    const std::string &get_url() const;

    //! Set the branch to used from the git repo with the manifest
    /*!
     *  \param[in] branch the branch to used from the git repo with the manifest
     */
    void set_branch(const std::string &branch);

    //! Get the branch to used from the git repo with the manifest
    /*!
     *  \return the branch to used from the git repo with the manifest
     */
    const std::string &get_branch() const;

    //! Set the name of the manifest file to use
    /*!
     *  \param[in] manifest_name the name of the manifest file to use
     */
    void set_manifest_name(const std::string &manifest_name);

    //! Get the name of the manifest file to use
    /*!
     *  \return the name of the manifest file to use
     */
    const std::string &get_manifest_name() const;

    //! Set if the manigest is known to be a Google repo tool manifest
    /*!
     *  \param[in] google_manifest if true, the manifest to use is a Google repo tool manifest
     */
    void set_google_manifest(bool google_manifest);

    //! Get if the manigest is known to be a Google repo tool manifest
    /*!
     *  \return if true, the manifest to use is a Google repo tool manifest
     */
    bool get_google_manifest() const;

    //! Set if the manigest is known to be a git super project
    /*!
     *  \param[in] git_super_project if true, the "manifest" to use is a git super project
     */
    void set_git_super_project(bool git_super_project);

    //! Get if the manifest is known to be a git super project
    /*!
     *  \return if true, the "manifest" to use is a git super project
     */
    bool get_git_super_project() const;

    //! Fetch the manifest regardless of its type
    /*!
     *  \return 0 if successdful, < 0 otherwise
     */
    Result fetch_manifest();

    //! Fetch the manifest of type Google repo tool
    /*!
     *  \return 0 if successdful, < 0 otherwise
     */
    Result fetch_google_manifest();

    //! Fetch the manifest of type ESysRepo
    /*!
     *  \return 0 if successdful, < 0 otherwise
     */
    Result fetch_esysrepo_manifest(GitHelper &git_helper, const std::string &git_repo_path,
                                const std::string &manifest_filename);

    Result read_esysrepo_manifest(std::shared_ptr<Manifest> manifest, const std::string &filename);
    Result read_esysrepo_manifest_xml(std::shared_ptr<Manifest> manifest, const std::string &filename);
    Result read_esysrepo_manifest_json(std::shared_ptr<Manifest> manifest, const std::string &filename);

    //! Fetch the "manifest" equivalent from a git super project
    /*!
     *  \return 0 if successdful, < 0 otherwise
     */
    Result fetch_git_super_project();

    //! Fetch and detect the manifest
    /*!
     *  \return 0 if successdful, < 0 otherwise
     */
    Result fetch_unknown_manifest();

    //! Create the ESysRepo config folder
    /*!
     *  \return 0 if successful, < 0 otherwise
     */
    Result create_esysrepo_folder();

    //! Load the ESysRepo config folder
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    Result load_esysrepo_folder();

    //! Init was already called before, calling it again on a valid ESysRepo config folder
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    Result load_esysrepo_folder_succeeded();

    //! Init was never already called before, or we failed to load the ESysRepo config folder
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    Result load_esysrepo_folder_failed();

    std::string get_extra_start_msg() override;

protected:
    //!< \cond DOXY_IMPL
    Result impl_run() override;

private:
    std::string m_url;                                        //!< The url for the git repo with the manifest
    std::string m_branch;                                     //!< The branch of the git
    std::string m_manifest_name;                              //!< The name of the manifest file
    bool m_google_manifest = false;                           //!< The manifest is a Google repo tool manifest
    bool m_git_super_project = false;                         //!< The reposotory hold a git super project
    manifest::Type m_manifest_type = manifest::Type::NOT_SET; //!< The type of the loaded manifest
    //!< \endcond
};

} // namespace esys::repo::exe
