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

#include <esys/log/mngr.h>

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

    std::shared_ptr<log::LoggerBase> get_logger(const std::string &name, const std::string &path);
    const std::string delete_create_temp_folder(const std::string &name);

    static TestCaseCtrl &get();

protected:
    static TestCaseCtrl *g_test_case;

    esystest::StdLogger m_logger;
    std::shared_ptr<esys::log::Mngr> m_log_mngr;
};

} // namespace test

} // namespace repo

} // namespace esys
