/*!
 * \file esys/repo/git/test/url01.cpp
 * \brief
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

#include <esys/repo/git/url.h>

#include <iostream>

namespace esys::repo::git::test
{

namespace url01
{

class Test
{
public:
    Test(const std::string &url0, const std::string &url1, bool same = true);

    const std::string &get_url0() const;
    const std::string &get_url1() const;
    bool get_same() const;

private:
    std::string m_url0;
    std::string m_url1;
    bool m_same = false;
};

Test::Test(const std::string &url0, const std::string &url1, bool same)
    : m_url0(url0)
    , m_url1(url1)
    , m_same(same)
{
}

const std::string &Test::get_url0() const
{
    return m_url0;
}

const std::string &Test::get_url1() const
{
    return m_url1;
}

bool Test::get_same() const
{
    return m_same;
}

/*! \class URL01 esys/repo/git/test/url01.cpp "esys/repo/git/test/url01.cpp"
 *  \brief
 */
ESYSTEST_AUTO_TEST_CASE(URL01)
{
    std::vector<Test> tests = {
        {"ssh://git@gitlab.com/libesys/esysrepo/esysrepo.git", "https://gitlab.com/libesys/esysrepo/esysrepo.git"},
        {"ssh://git@gitlab.com/libesys/esysrepo/esysrepo", "https://gitlab.com/libesys/esysrepo/esysrepo.git"},
        {"ssh://git@gitlab.com/libesys/esysrepo/esysrepo.git", "https://gitlab.com/libesys/esysrepo/esysrepo"},
        {"ssh://git@gitlab.com/libesys/esysrepo/esysrepo", "https://gitlab.com/libesys/esysrepo/esysrepo"},
        {"ssh://gitlab.com/libesys/esysrepo/esysrepo", "https://gitlab.com/libesys/esysrepo/esysrepo.git"}};

    for (auto &test : tests)
    {
        URL url(test.get_url0());

        bool result = url == test.get_url1();
        ESYSTEST_REQUIRE_EQUAL(result, test.get_same());
    }
}

} // namespace url01

} // namespace esys::repo::git::test
