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

#include "esys/repo/test/esysrepo_t_prec.h"
#include "esys/repo/test/testcasectrl.h"

#include <iostream>
#include <cassert>

namespace esys
{

namespace repo
{

namespace test
{

TestCaseCtrl *TestCaseCtrl::g_test_case = nullptr;

TestCaseCtrl &TestCaseCtrl::get()
{
    assert(g_test_case != nullptr);

    return *g_test_case;
}

TestCaseCtrl::TestCaseCtrl()
    : esystest::TestCaseCtrl()
{
    g_test_case = this;

    AddSearchPathEnvVar("ESYSREPO");
    AddSearchPath("res/esysrepo_t");                    // If cwd is root of the emdev git repo
    AddSearchPath("../../src/esysrepo/res/esysrepo_t"); // if cwd is the bin folder

    m_logger.Set(&std::cout);
    esystest::Logger::Set(&m_logger);
}

TestCaseCtrl::~TestCaseCtrl()
{
}

ESYSTEST_GLOBAL_FIXTURE(TestCaseCtrl);

} // namespace test

} // namespace repo

} // namespace esys
