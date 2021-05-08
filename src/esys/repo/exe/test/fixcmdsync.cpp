/*!
 * \file esys/repo/exe/test/fixcmdsync.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/test/esysrepo_t_prec.h"
#include "esys/repo/exe/test/fixcmdsync.h"

#include <fstream>

namespace esys
{

namespace repo
{

namespace exe
{

namespace test
{

FixCmdSync::FixCmdSync()
{
}

void FixCmdSync::set_manifest_url(const std::string &manifest_url)
{
    m_manifest_url = manifest_url;
}

const std::string &FixCmdSync::get_manifest_url() const
{
    return m_manifest_url;
}

void FixCmdSync::set_manifest_branch(const std::string &manifest_branch)
{
    m_manifest_branch = manifest_branch;
}

const std::string &FixCmdSync::get_manifest_branch() const
{
    return m_manifest_branch;
}

void FixCmdSync::set_temp_sub_folder(const std::string &temp_sub_folder)
{
    m_temp_sub_folder = temp_sub_folder;
}

const std::string &FixCmdSync::get_temp_sub_folder() const
{
    return m_temp_sub_folder;
}

const boost::filesystem::path &FixCmdSync::get_file_path() const
{
    return m_file_path;
}

int FixCmdSync::test_file_content(const std::string &filename, const std::string &content)
{
    boost::filesystem::path file_path = get_file_path();
    file_path /= filename;

    std::ifstream fin(file_path.string().c_str());

    if (!fin.is_open()) return -1;

    std::string str;

    fin.seekg(0, std::ios::end);
    str.reserve(fin.tellg());
    fin.seekg(0, std::ios::beg);

    str.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());

    if (str == content) return 0;
    return -2;
}

void FixCmdSync::test_basic_files()
{
    int result;

    result = test_file_content("test.txt", "3");
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    result = test_file_content("src/test_a/test.txt", "a");
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    result = test_file_content("src/test_a_b/test.txt", "a_b");
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    result = test_file_content("src/test_b/test.txt", "b");
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    result = test_file_content("src/commit_a/test.txt", "a");
    ESYSTEST_REQUIRE_EQUAL(result, 0);
}

void FixCmdSync::init()
{
    auto &ctrl = repo::test::TestCaseCtrl::get();

    ESYSTEST_REQUIRE_EQUAL(get_temp_sub_folder().empty(), false);
    m_file_path = ctrl.delete_create_temp_folder(get_temp_sub_folder());
    ESYSTEST_REQUIRE_EQUAL(m_file_path.string().empty(), false);

    m_logger = ctrl.get_logger("logger", m_file_path.string());
    ESYSTEST_REQUIRE_NE(m_logger, nullptr);

    m_git = std::make_shared<libgit2::Git>();
    m_git->set_logger_if(m_logger);

    ESYSTEST_REQUIRE_EQUAL(get_manifest_url().empty(), false);

    m_cmd_init.set_url(get_manifest_url());
    if (!get_manifest_branch().empty()) m_cmd_init.set_branch(get_manifest_branch());
    m_cmd_init.set_parent_path(m_file_path.string());
    m_cmd_init.set_git(m_git);
    m_cmd_init.set_logger_if(m_logger);
    m_cmd_init.set_debug(true);

    int result = m_cmd_init.run();
    ESYSTEST_REQUIRE_EQUAL(result, 0);
}

void FixCmdSync::sync()
{
    m_cmd_sync.set_job_count(4);
    m_cmd_sync.set_parent_path(m_file_path.string());
    m_cmd_sync.set_git(m_git);
    m_cmd_sync.set_logger_if(m_logger);
    m_cmd_sync.set_debug(true);

    int result = m_cmd_sync.run();
    ESYSTEST_REQUIRE_EQUAL(result, 0);
}

void FixCmdSync::run()
{
    init();
    sync();
}

int FixCmdSync::open_git_manifest_repo()
{
    if (get_git() == nullptr) return -1;
    if (get_git()->is_open()) return -2;

    auto config_folder = m_cmd_init.get_config_folder();
    if (config_folder == nullptr) return -3;

    auto config = config_folder->get_config();
    boost::filesystem::path manifest_path = config_folder->get_path();
    manifest_path /= config->get_manifest_path();
    manifest_path = manifest_path.parent_path().normalize().make_preferred();

    return get_git()->open(manifest_path.string());
}

int FixCmdSync::close_git()
{
    if (get_git() == nullptr) return -1;
    if (!get_git()->is_open()) return -2;

    get_git()->close();
    return 0;
}

std::shared_ptr<libgit2::Git> FixCmdSync::get_git()
{
    return m_git;
}

CmdInit &FixCmdSync::get_cmd_init()
{
    return m_cmd_init;
}

CmdSync &FixCmdSync::get_cmd_sync()
{
    return m_cmd_sync;
}

} // namespace test

} // namespace exe

} // namespace repo

} // namespace esys
