/*!
 * \file esys/repo/libgit2/gitimpl.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2021 Michel Gillet
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
#include "esys/repo/ssh.h"

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
    int get_branches(git::Branches &branches, git::BranchType branch_type = git::BranchType::LOCAL);

    int clone(const std::string &url, const std::string &path, const std::string &branch = "");
    int checkout(const std::string &branch, bool force = false);
    int reset(const git::Commit &commit, git::ResetType type = git::ResetType::SOFT);
    int fastforward(const git::Commit &commit);
    
    int get_last_commit(git::Commit &commit);
    int get_parent_commit(const git::Commit &commit, git::Commit &parent, int nth_parent = 1);

    int is_dirty(bool &dirty);
    int is_detached(bool &detached);

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

    bool is_ssh_agent_running();

    int merge_analysis(const std::vector<std::string> &refs, git::MergeAnalysisResult &merge_analysis_result,
                       std::vector<git::Commit> &commits);

    int fetch(const std::string &remote);

    int resolve_ref(git_annotated_commit **commit, const std::string &ref);
    int resolve_ref(git_reference **ref, const std::string &ref_str);
    int resolve_ref(git_reference **ref, git_annotated_commit **commit, const std::string &ref_str);

    int find_ref(git_annotated_commit **commit, const std::string &ref, std::string &new_ref);
    int find_ref(git_reference **ref, git_annotated_commit **commit, const std::string &ref_str, std::string &new_ref);

    int convert_bin_hex(const git_oid &oid, std::string &hex_str);
    int convert_hex_bin(const std::string &hex_str, git_oid &oid);

protected:
    static std::unique_ptr<LibGit2> s_libgt2;

    static int libgit2_credentials_cb(git_credential **out, const char *url, const char *name, unsigned int types,
                                      void *payload);
    static int libgit2_sideband_progress_cb(const char *str, int len, void *data);
    static int libgit2_transfer_progress_cb(const git_indexer_progress *stats, void *payload);
    static int libgit2_update_tips_cb(const char *refname, const git_oid *a, const git_oid *b, void *data);
    static int libgit2_pack_progress_cb(int stage, uint32_t current, uint32_t total, void *payload);

    Git *m_self = nullptr;
    git_repository *m_repo = nullptr;
    Guard<git_credential> m_credential;
    SSH m_ssh;
};

} // namespace libgit2

} // namespace repo

} // namespace esys
