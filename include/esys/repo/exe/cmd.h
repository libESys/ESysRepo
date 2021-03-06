/*!
 * \file esys/repo/exe/cmd.h
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
#include "esys/repo/gitbase.h"
#include "esys/repo/manifest.h"
#include "esys/repo/manifest/type.h"
#include "esys/repo/manifest/loader.h"
#include "esys/repo/configfolder.h"
#include "esys/repo/githelper.h"
#include "esys/repo/result.h"

#include <esys/log/user.h>
#include <esys/log/mngr.h>

#include <chrono>
#include <memory>

//<swig_inc/>

//<swig>%shared_ptr(esys::repo::exe::Cmd);</swig>

namespace esys::repo
{

namespace cli
{
class ESYSREPO_API Cmd;
class ESYSREPO_API AppBase;
} // namespace cli

namespace exe
{

/*! \class Cmd esys/repo/exe/cmd.h "esys/repo/exe/cmd.h"
 * \brief Base class of all commands of the ESysRepo tool
 */
class ESYSREPO_API Cmd : public log::User
{
public:
    static const int THOUSAND = 1000;

    //! Default constructor
    explicit Cmd(const std::string &name);

    //! Destructor
    ~Cmd() override;

    const std::string &get_name() const;

    void set_job_count(int job_count);
    int get_job_count() const;

    //! Set the manifest
    /*!
     * \param[in] manifest the manifest
     */
    void set_manifest(std::shared_ptr<Manifest> manifest);

    //! Get the manifest
    /*!
     * \retrun the manifest
     */
    std::shared_ptr<Manifest> get_manifest() const;

    //! Set the git instance
    /*!
     * \param[in] git the git instance
     */
    void set_git(std::shared_ptr<GitBase> git);

    //! Get the git instance
    /*!
     * \return the git instance
     */
    std::shared_ptr<GitBase> get_git() const;

    //! Set the parent path
    /*!
     * \param[in] parent_path the parent path
     */
    void set_workspace_path(const std::string &workspace_path);

    //! Get the parent path
    /*!
     * \return the parent path
     */
    const std::string &get_workspace_path() const;

    //! Set the config folder
    /*!
     * \param[in] config_folder the config folder
     */
    void set_config_folder(std::shared_ptr<ConfigFolder> config_folder);

    //! Get the config folder
    /*!
     * \retrun the config folder
     */
    std::shared_ptr<ConfigFolder> get_config_folder();

    //! Set the manifest loader to use
    /*!
     * \param[in] loader the manifest loader to use
     */
    void set_loader(std::shared_ptr<manifest::Loader> loader);

    //! Get the manifest loader to use
    /*!
     * \return the manifest loader to use
     */
    std::shared_ptr<manifest::Loader> get_loader();

    //! Find the workspace path if any given a child path
    /*!
     * \param[in] path the child path is provided, otherwise the current path will be used
     * \return the workspace path if found, empty string otherwise
     */
    static std::string find_workspace_path(const std::string &path = "");

    //! Find the path of a git repo if any given a child path
    /*!
     * \param[in] path the child path is provided, otherwise the current path will be used
     * \return the path of the git reop if found, empty string otherwise
     */
    static std::string find_git_repo_path(const std::string &path = "");

    //! Do the work
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    virtual Result run();

    //! Set if debug information are printed or not
    /*!
     * \param[in] debug if true debug information are printed
     */
    void set_debug(bool debug = true);

    //! Get if debug information are printed or not
    /*!
     * \return if true debug information are printed
     */
    bool get_debug() const;

    //! Set folder in use and find the parent path for it
    /*!
     * \param[in] folder the folder
     */
    void set_folder(const std::string &folder);

    //! Get folder in use
    /*!
     * \return the folder
     */
    const std::string &get_folder() const;

    virtual void set_sub_args(const std::vector<std::string> &sub_args);
    const std::vector<std::string> &get_sub_args() const;

    void set_time(bool time);
    bool get_time() const;
    void set_delta_time(bool delta_time);
    bool get_delta_time() const;

    void set_groups(const std::vector<std::string> &groups);
    const std::vector<std::string> &get_groups() const;

    void set_cli_cmd(cli::Cmd *cli_cmd);
    cli::Cmd *get_cli_cmd();

    void set_app_base(cli::AppBase *app_base);
    cli::AppBase *get_app_base();

    int process_sub_args_as_git_repo_path(const std::string &input_path);
    Result process_sub_args_as_git_repo_paths();
    const std::vector<std::string> &get_input_git_repo_paths() const;

    virtual std::string get_extra_start_msg();

    void set_console_os(std::ostream *console_os);
    std::ostream *get_console_os();

    Result default_handling_folder_workspace();
    Result only_one_folder_or_workspace();

    int create_logger(const std::string &path = "");

    std::shared_ptr<esys::log::Mngr> get_logger_mngr();

    const std::string &get_logger_name() const;
    void set_logger_name(const std::string &logger_name);

    void debug(int level, const std::string &msg) override;
    void info(const std::string &msg) override;
    void warn(const std::string &msg) override;
    void error(const std::string &msg) override;
    void critical(const std::string &msg) override;
    void log(log::Level level, const std::string &msg) override;
    void log(const std::string &msg, log::Level level, int debug_level = 0) override;

    void clean_cout();

    void print_cmd_name();
    void print_cmd_name(std::ostream &os);

    Result generic_error(int error);
protected:
    //!< \cond DOXY_IMPL

    void set_print_cmd_name_by_base(bool print_cmd_name_by_base);
    bool get_print_cmd_name_by_base() const;
    std::shared_ptr<GitHelper> new_git_helper();

    virtual Result impl_run() = 0;

    //! Helper function to open the ESysRep config folder and file
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    Result open_esysrepo_folder();

    //! Helper function to load the manifest
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    Result load_manifest();


private:
    std::string m_name;
    std::shared_ptr<Manifest> m_manifest;          //!< The manifest to use
    std::shared_ptr<GitBase> m_git;                //!< The git instance to use
    bool m_debug = false;                          //!< If true debug information is printed
    std::string m_folder;                          //!< The current folder
    std::string m_workspace_path;                  //!< The workspace path
    std::shared_ptr<ConfigFolder> m_config_folder; //!< The config folder
    std::shared_ptr<manifest::Loader> m_loader;    //!< The manifest loader
    std::chrono::time_point<std::chrono::steady_clock> m_start_time;
    std::vector<std::string> m_sub_args;
    std::vector<std::string> m_input_rel_git_repo_paths;
    std::vector<std::string> m_groups;
    int m_job_count = 1;
    bool m_time = false;
    bool m_delta_time = false;
    cli::Cmd *m_cli_cmd = nullptr;
    cli::AppBase *m_app_base = nullptr;
    std::ostream *m_console_os = nullptr;
    bool m_print_cmd_name_by_base = true;
    std::shared_ptr<esys::log::Mngr> m_logger_mngr;
    std::string m_logger_name = "logger";
    //!< \endcond
};

} // namespace exe

} // namespace esys::repo
