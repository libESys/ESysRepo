/*!
 * \file esys/repo/git/test/sortbranches01.cpp
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

#include "esys/repo/test/esysrepo_t_prec.h"

#include <esys/repo/git/branches.h>

#include <boost/filesystem.hpp>

#include <iostream>

namespace esys
{

namespace repo
{

namespace git
{

namespace test
{

/*! \class SortBranches01 esys/repo/git/test/sortbranches01.cpp "esys/repo/git/test/sortbranches01.cpp"
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(SortBranches01)
{
    std::vector<Branch> branches_raw = {{"master", false}, {"develop", true}};
    Branches branches(branches_raw);

    branches.sort();
    ESYSTEST_REQUIRE_EQUAL(branches.get()[0]->get_name(), "develop");

    std::vector<git::Branch> branches1_raw = {{"master", false}, {"develop", false}};
    Branches branches1(branches1_raw);

    branches1.sort();
    ESYSTEST_REQUIRE_EQUAL(branches1.get()[0]->get_name(), "master");
}

} // namespace test

} // namespace git

} // namespace repo

} // namespace esys
