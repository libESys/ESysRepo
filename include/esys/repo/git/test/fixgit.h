/*!
 * \file esys/repo/git/test/fixgit.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * __legal_e__
 * \endcond
 *
 */

#include <esys/repo/git.h>

#include <iostream>
#include <memory>

namespace esys
{

namespace repo
{

namespace git
{

namespace test
{

/*! \class FixGit esys/repo/exe/test/fixgit.h "esys/repo/exe/test/fixgit.h"
 *  \brief
 */
class FixGit
{
public:
    FixGit();
    FixGit(std::shared_ptr<Git> git);

    int reset_to_parent(int nth_parent = 1);

    void set_git(std::shared_ptr<Git> git);
    std::shared_ptr<Git> get_git();

protected:
    std::shared_ptr<Git> m_git;
};

} // namespace test

} // namespace git

} // namespace repo

} // namespace esys
