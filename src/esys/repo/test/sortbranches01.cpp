/*!
 * \file esys/repo/test/sortbranches01.cpp
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

#include <esys/repo/gitbase.h>

#include <boost/filesystem.hpp>

#include <iostream>

namespace esys
{

namespace repo
{

namespace test
{

/*! \class SortBranches01 esys/repo/test/sortbranches01.cpp "esys/repo/test/sortbranches01.cpp"
 *
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(SortBranches01)
{
    std::vector<git::Branch> branches = {{"master", false}, {"develop", true}};

    GitBase::sort_branches(branches);
    ESYSTEST_REQUIRE_EQUAL(branches[0].get_name(), "develop");

    std::vector<git::Branch> branches1 = {{"master", false}, {"develop", false}};

    GitBase::sort_branches(branches1);
    ESYSTEST_REQUIRE_EQUAL(branches1[0].get_name(), "master");
}

} // namespace test

} // namespace repo

} // namespace esys
