/*!
 * \file esys/repo/libgit2/gitimpl.h
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
#include "esys/repo/libgit2/git.h"
#include "esys/repo/libgit2/libgit2.h"
#include "esys/repo/libgit2/guard.h"
#include "esys/repo/git/diffdelta.h"

#include <git2.h>

#include <memory>

namespace esys
{

namespace repo
{

namespace libgit2
{

class ESYSREPO_API GitImpl
{
public:
    GitImpl(Git *self);
    ~GitImpl();

    int open(const std::string &folder);
    bool is_open();

    int close();
    int get_remotes(std::vector<git::Remote> &remotes);
    int get_branches(std::vector<git::Branch> &branches, git::BranchType branch_type = git::BranchType::LOCAL);

    int clone(const std::string &url, const std::string &path);
    int checkout(const std::string &branch, bool force = false);

    int get_last_commit(git::Commit &commit);

    int is_dirty(bool &dirty);
    int get_status(git::RepoStatus &repo_status);
    int handle_status_entry(git::RepoStatus &repo_status, const git_status_entry *status_entry);
    int handle_status_entry_current(git::RepoStatus &repo_status, std::shared_ptr<git::Status> status,
                                    const git_status_entry *status_entry);
    int handle_status_entry_index(git::RepoStatus &repo_status, std::shared_ptr<git::Status> status,
                                  const git_status_entry *status_entry);
    int handle_status_entry_work_dir(git::RepoStatus &repo_status, std::shared_ptr<git::Status> status,
                                     const git_status_entry *status_entry);
    int handle_status_entry_conflicted(git::RepoStatus &repo_status, std::shared_ptr<git::Status> status,
                                       const git_status_entry *status_entry);
    int handle_status_entry_ignored(git::RepoStatus &repo_status, std::shared_ptr<git::Status> status,
                                    const git_status_entry *status_entry);

    int from_to(git_status_t status, std::shared_ptr<git::Status> status_ptr);
    int from_to(const git_diff_delta *delta, git::DiffDelta &diff_delta);
    int from_to(const git_diff_file &file, git::DiffFile &diff_file);

    int check_error(int result, const std::string &action = "");

    const std::string &get_version();
    const std::string &get_lib_name();

    static const std::string &s_get_version();
    static const std::string &s_get_lib_name();

    static const std::string &s_get_ssh_version();
    static const std::string &s_get_ssh_lib_name();

    Git *self() const;

    static int libgit2_credentials(git_credential **out, const char *url, const char *name, unsigned int types,
                                   void *payload);
    bool is_ssh_agent_running();

    int merge_analysis(const std::vector<std::string> &refs, git::MergeAnalysisResult &merge_analysis_result,
                       std::vector<git::Commit> &commits);

    int resolve_ref(git_annotated_commit **commit, const std::string &ref);

    int convert_bin_hex(const git_oid &oid, std::string &hex_str);

protected:
    static std::unique_ptr<LibGit2> s_libgt2;

    Git *m_self = nullptr;
    git_repository *m_repo = nullptr;
    Guard<git_credential> m_credential;
};

} // namespace libgit2

} // namespace repo

} // namespace esys
