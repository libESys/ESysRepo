/*!
 * \file esys/repo/manifest/test/globymatch01.cpp
 * \brief For precompiled headers
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2021 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/test/esysrepo_t_prec.h"

#include <esys/repo/manifest/syncrepos.h>

namespace esys
{

namespace repo
{

namespace manifest
{

namespace test
{

/*! \class GlobyMatch01 esys/repo/manifest/test/globymatch01.cpp
 * "esys/repo/manifest/test/globymatch01.cpp"
 *
 *  \brief
 *
 */
ESYSTEST_AUTO_TEST_CASE(GlobyMatch01)
{
    struct Test
    {
        Test(const std::string &str, const std::string &glob, bool match = true)
            : m_str(str)
            , m_glob(glob)
            , m_match(match)
        {
        }

        std::string m_str;
        std::string m_glob;
        bool m_match = false;
    };

    std::vector<Test> tests = {
        {"src/repo", "*", false},
        {"src/repo", "src/*", true},
        {".", "*", true},
        {"src/repo", "src/r?po", true},
        {"src/repo", "src/*p?", true},
    };

    bool result = false;

    for (auto &test : tests)
    {
        result = SyncRepos::globly_match(test.m_str, test.m_glob);
        ESYSTEST_REQUIRE_EQUAL(result, test.m_match);
    }
}

} // namespace test

} // namespace manifest

} // namespace repo

} // namespace esys
