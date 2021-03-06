/*!
 * \file esys/repo/exe/test/fixcmdsync.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * __legal_e__
 * \endcond
 *
 */

#include <esys/repo/libgit2/git.h>
#include <esys/repo/exe/cmdinit.h>
#include <esys/repo/exe/cmdsync.h>
#include <esys/repo/exe/cmdmanifest.h>
#include <esys/repo/filesystem.h>

#include <boost/filesystem.hpp>

#include <iostream>

namespace esys
{

namespace repo
{

namespace exe
{

namespace test
{

/*! \class FixCmd esys/repo/exe/test/fixcmd.h "esys/repo/exe/test/fixcmd.h"
 *  \brief
 */
class FixCmd
{
public:
    FixCmd();

    void set_manifest_url(const std::string &manifest_url);
    const std::string &get_manifest_url() const;

    void set_manifest_branch(const std::string &manifest_branch);
    const std::string &get_manifest_branch() const;

    void set_temp_sub_folder(const std::string &temp_sub_folder);
    const std::string &get_temp_sub_folder() const;
    std::string get_temp_folder() const;

    const boost::filesystem::path &get_file_path() const;

    int test_file_content(const std::string &filename, const std::string &content);
    void test_repo_exists(const std::string &path, bool exists = true);
    void test_repo_head(const std::string &path, const std::string &head_name);

    void test_basic_files();

    void run();
    void init();
    void sync();
    void sync(const std::vector<std::string> folders);
    void manifest();

    int open_git_manifest_repo();
    void test_manifest_repo_head(const std::string &head_name);
    int close_git();
    std::shared_ptr<libgit2::Git> get_git();

    CmdInit &get_cmd_init();
    CmdSync &get_cmd_sync();
    CmdManifest &get_cmd_manifest();

protected:
    boost::filesystem::path m_file_path;
    CmdInit m_cmd_init;
    CmdSync m_cmd_sync;
    CmdManifest m_cmd_manifest;
    std::shared_ptr<log::LoggerBase> m_logger;
    std::shared_ptr<libgit2::Git> m_git;
    std::string m_manifest_url;
    std::string m_manifest_branch;
    std::string m_temp_sub_folder;
};

} // namespace test

} // namespace exe

} // namespace repo

} // namespace esys
