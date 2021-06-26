/*!
 * \file esys/repo/exe/test/fixgit.cpp
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
#include "esys/repo/git/test/fixgit.h"

namespace esys
{

namespace repo
{

namespace git
{

namespace test
{

FixGit::FixGit()
{
}

FixGit::FixGit(std::shared_ptr<Git> git)
    : m_git(git)
{
}

int FixGit::reset_to_parent(int nth_parent)
{
    if (get_git() == nullptr) return -1;

    git::Commit last_commit;
    git::Commit parent_commit;

    // Get the last commit in the manifest git repo
    int result = get_git()->get_last_commit(last_commit);
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    // Get the its parent commit
    result = get_git()->get_parent_commit(last_commit, parent_commit);
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    // Reset the manifest git repo to the parent commit
    result = get_git()->reset(parent_commit, git::ResetType::HARD);
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    git::Commit new_last_commit;

    // Get the new last commit
    result = get_git()->get_last_commit(new_last_commit);
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    // The new last commit should be the parent commit
    ESYSTEST_REQUIRE_EQUAL(parent_commit.get_hash(), new_last_commit.get_hash());
    return 0;
}

void FixGit::set_git(std::shared_ptr<Git> git)
{
    m_git = git;
}

std::shared_ptr<Git> FixGit::get_git()
{
    return m_git;
}

} // namespace test

} // namespace git

} // namespace repo

} // namespace esys
