/*!
 * \file esys/repo/githelper.h
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
#include "esys/repo/result.h"

#include <esys/log/user.h>

#include <memory>

//<swig_inc/>

//<swig>%shared_ptr(esys::repo::GitHelper);</swig>

namespace esys::repo
{

/*! \class GitBase esys/repo/githelper.h "esys/repo/githelper.h"
 * \brief Git helper class
 *
 * It wraps a GiBase instance and provides the same functionality, but with automatic logging of the
 * execution.
 */
class ESYSREPO_API GitHelper : public log::User
{
public:
    static const int THOUSAND = 1000;
    static const int CLEAN_OUT_REPETITION = 8;

    //! Constructor
    GitHelper(std::shared_ptr<GitBase> git = nullptr, std::shared_ptr<log::Logger_if> log_if = nullptr,
              int repo_idx = -1);

    //! Destructor
    ~GitHelper() override;

    void debug(int level, const std::string &msg) override;
    void info(const std::string &msg) override;
    void warn(const std::string &msg) override;
    void error(const std::string &msg) override;
    void critical(const std::string &msg) override;
    void log(log::Level level, const std::string &msg) override;
    void log(const std::string &msg, log::Level level, int debug_level = 0) override;

    void error(const std::string &msg, int result) override;
    void done(const std::string &msg, uint64_t elapsed_time);

    //<swig>%rename(open_folder) open;</swig>
    Result open(const std::string &folder, log::Level log_level, int debug_level = 0);

    Result clone(const std::string &url, const std::string &path, bool do_close, log::Level log_level,
                 int debug_level = 0);
    Result clone_branch(const std::string &url, const std::string &branch, const std::string &path, bool do_close,
                        log::Level log_level, int debug_level = 0);
    Result clone(const std::string &url, const std::string &temp_path, const std::string &path, bool do_close,
                 log::Level log_level, int debug_level = 0);

    Result close(log::Level log_level, int debug_level = 0);

    Result fastforward(const git::CommitHash &commit, log::Level log_level, int debug_level = 0);

    Result fetch(const std::string &remote, log::Level log_level, int debug_level = 0);
    Result fetch(log::Level log_level, int debug_level = 0);

    Result get_branches(git::Branches &branches, git::BranchType branch_type, log::Level log_level,
                        int debug_level = 0);

    bool has_branch(const std::string &name, git::BranchType branch_type, log::Level log_level, int debug_level = 0);

    Result get_hash(const std::string &revision, std::string &hash, log::Level log_level, int debug_level = 0);

    Result get_hash_local(const std::string &revision, std::string &hash, log::Level log_level, int debug_level = 0);

    Result is_dirty(bool &dirty, log::Level log_level, int debug_level = 0);
    Result is_detached(bool &detached, log::Level log_level, int debug_level = 0);

    Result get_status(git::RepoStatus &status, log::Level log_level, int debug_level = 0);

    Result checkout(const std::string &branch, bool force, log::Level log_level, int debug_level = 0);

    Result merge_analysis(const std::vector<std::string> &refs, git::MergeAnalysisResult &merge_analysis_result,
                       std::vector<git::CommitHash> &commits, log::Level log_level, int debug_level = 0);

    Result move(const std::string &src, const std::string &dst, bool recursive, log::Level log_level,
                int debug_level = 0);

    //! Set the GitBase instance to use
    /*!
     * \param[in] git the GitBase instance to use
     */
    void set_git(std::shared_ptr<GitBase> git);

    //! Get the GitBase instance to use
    /*!
     * \return the GitBase instance to use
     */
    std::shared_ptr<GitBase> get_git() const;

    void set_auto_close(bool auto_close = true);
    bool get_auto_close() const;

    void set_repo_idx(int repo_idx);
    int get_repo_idx() const;
    void set_display_repo_idx(bool display_repo_idx);
    bool get_display_repo_idx() const;

    void init_oss(std::ostringstream &oss);
    void init_oss(std::ostringstream &oss, const std::string &msg);
    void init_oss_done();
    void init_oss_clear();
    bool is_init_oss_done();

    void clean_cout();

private:
    //!< \cond DOXY_IMPL
    std::weak_ptr<GitBase> m_git; //!< The GitBase instance to use
    int m_repo_idx = -1;          //!< The index of the repository worked on
    bool m_display_repo_idx = true;
    bool m_auto_close = false;
    bool m_init_oss_done = false;
    //!< \endcond
};

} // namespace esys::repo
