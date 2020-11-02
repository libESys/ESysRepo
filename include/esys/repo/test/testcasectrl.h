/*!
 * \file esys/repo/test/testcasectrl.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * __legal_e__
 * \endcond
 *
 */

#pragma once

#include <esystest/testcasectrl.h>
#include <esystest/stdlogger.h>

namespace esys
{

namespace repo
{

namespace test
{

class TestCaseCtrl : public esystest::TestCaseCtrl
{
public:
    TestCaseCtrl();
    virtual ~TestCaseCtrl();

    static TestCaseCtrl &get();

protected:
    static TestCaseCtrl *g_test_case;

    esystest::StdLogger m_logger;
};

} // namespace test

} // namespace repo

} // namespace esys
