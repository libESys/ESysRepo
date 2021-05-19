/*!
 * \file esys/repo/manifest/test/task_t01_manifest.cpp
 * \brief For precompiled headers
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

#include <esys/repo/manifest/task_t.h>

#include <boost/filesystem.hpp>

#include <iostream>
#include <memory>

namespace esys
{

namespace repo
{

namespace manifest
{

namespace test
{

namespace task_t01
{

class TestMe
{
public:
    TestMe();

    int add(int a, int b);
    int add1(std::shared_ptr<Repository> repo, int a, int b);
};

TestMe::TestMe()
{
}

int TestMe::add(int a, int b)
{
    return a + b;
}

int TestMe::add1(std::shared_ptr<Repository> repo, int a, int b)
{
    return a + b;
}

/*! \class Task_t01Manifest esys/repo/manifest/test/task_t01_manifest.cpp
 * "esys/repo/manifest/test/task_t01_manifest.cpp"
 *
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(Task_t01Manifest)
{
    std::shared_ptr<Repository> repo = std::make_shared<Repository>();
    std::shared_ptr<TestMe> test_me = std::make_shared<TestMe>();

    Task_t task_t0(test_me, &TestMe::add, 2, 3);

    int result = task_t0.run();
    ESYSTEST_REQUIRE_EQUAL(result, 5);

    Task_t task_t1(test_me, &TestMe::add1, repo, 2, 3);

    result = task_t1.run();
    ESYSTEST_REQUIRE_EQUAL(result, 5);
}

} // namespace task_t01

} // namespace test

} // namespace manifest

} // namespace repo

} // namespace esys
