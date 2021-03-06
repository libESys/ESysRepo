/*!
 * \file esys/repo/test/testcasectrl.h
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
#include "esys/repo/test/testcasectrl.h"

#include <esys/repo/filesystem.h>

#include <esys/log/mngr.h>

#include <boost/filesystem.hpp>

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

    m_log_mngr = esys::log::Mngr::get();
}

TestCaseCtrl::~TestCaseCtrl()
{
}

std::shared_ptr<log::LoggerBase> TestCaseCtrl::get_logger(const std::string &name, const std::string &path)
{
    auto logger = m_log_mngr->new_logger(log::LoggerType::SPDLOG, name);
    if (logger == nullptr) return nullptr;

    log::Level level = log::Level::DEBUG;

    logger->add_console(level);
    boost::filesystem::path log_path = path;
    log_path /= "log.txt";
    logger->add_basic_file(log_path.string());
    logger->set_log_level(level);
    logger->set_debug_level(5);
    logger->set_flush_log_level(level);
    return logger;
}

const std::string TestCaseCtrl::delete_create_temp_folder(const std::string &name)
{
    boost::filesystem::path file_path = GetTempFilesFolder();
    file_path /= name;

    bool remove_all = true;

    try
    {
        if (boost::filesystem::exists(file_path)) boost_no_all::remove_all(file_path.string());
    }
    catch (const boost::filesystem::filesystem_error &e)
    {
        remove_all = false;
        std::cerr << e.what() << std::endl;
    }

    if (!remove_all) return "";

    bool created = boost::filesystem::create_directory(file_path);
    if (!created) return "";
    return file_path.string();
}

ESYSTEST_GLOBAL_FIXTURE(TestCaseCtrl);

} // namespace test

} // namespace repo

} // namespace esys
