/*!
 * \file esys/repo/libgit2/test/walkcommits01_libgit2.cpp
 * \brief For precompiled headers
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

#include "esys/repo/test/esysrepo_t_prec.h"

#include <esys/repo/libgit2/git.h>
#include <esys/repo/filesystem.h>

#include <boost/filesystem.hpp>

#include <iostream>
#include <vector>

namespace esys::repo::libgit2::test
{

namespace walk_commits01
{

class TheWalkCommit : public git::WalkCommit
{
public:
    ~TheWalkCommit() override;

    virtual int new_commit(GitBase *git_base, std::shared_ptr<git::Commit> commit) override;

    std::vector<std::shared_ptr<git::Commit>> get_commits();
    const std::vector<std::shared_ptr<git::Commit>> get_commits() const;

protected:
    std::vector<std::shared_ptr<git::Commit>> m_commits;
};

TheWalkCommit::~TheWalkCommit()
{
    m_commits.clear();
}

int TheWalkCommit::new_commit(GitBase *git_base, std::shared_ptr<git::Commit> commit)
{
    m_commits.push_back(commit);

    return 0;
}

std::vector<std::shared_ptr<git::Commit>> TheWalkCommit::get_commits()
{
    return m_commits;
}

const std::vector<std::shared_ptr<git::Commit>> TheWalkCommit::get_commits() const
{
    return m_commits;
}

/*! \class WalkCommits01LibGit2 esys/repo/libgit2/test/walkcommits01_libgit2.cpp
 * "esys/repo/libgit2/test/walkcommits01_libgit2.cpp"
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(WalkCommits01LibGit2)
{
    boost::filesystem::path file_path;

    file_path = repo::test::TestCaseCtrl::get().GetTempFilesFolder();
    file_path /= ("walkcommits01libgit2");

    std::cout << "Temp folder = " << file_path << std::endl;

    bool remove_all = true;

    try
    {
        if (boost::filesystem::exists(file_path)) boost_no_all::remove_all(file_path.string());
    }
    catch (const boost::filesystem::filesystem_error &e)
    {
        remove_all = false;
        std::cerr << e.what() << std::endl;
    }

    ESYSTEST_REQUIRE_EQUAL(remove_all, true);

    bool created = boost::filesystem::create_directory(file_path);
    ESYSTEST_REQUIRE_EQUAL(created, true);

    Git git;

    Result result = git.clone("https://gitlab.com/libesys/esysrepo/test_google_manifest.git",
                           file_path.normalize().make_preferred().string());
    if (result.error()) std::cout << "ERROR " << result << std::endl;
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);

    auto the_walk_commit = std::make_shared<TheWalkCommit>();

    result = git.walk_commits(the_walk_commit);
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);

    result = git.close();
    ESYSTEST_REQUIRE_EQUAL(result.ok(), true);

    ESYSTEST_REQUIRE_EQUAL(the_walk_commit->get_commits().size(), 4);
}

} // namespace walk_commits01

} // namespace esys::repo::libgit2::test
