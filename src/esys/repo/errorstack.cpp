/*!
 * \file esys/repo/errorstack.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/errorstack.h"

#include <sstream>

namespace esys::repo
{

ErrorStack::ErrorStack() = default;

ErrorStack::ErrorStack(const Result &result)
    : m_result(result)
{
}

ErrorStack::~ErrorStack() = default;

int ErrorStack::analyze()
{
    if (get_result().ok()) return 0;

    m_error_infos.clear();

    std::shared_ptr<ErrorInfo> cur_error_info = get_result().get_error_info();

    while (cur_error_info != nullptr)
    {
        m_error_infos.push_back(cur_error_info);

        cur_error_info = cur_error_info->get_prev();
    }

    return print();
}

int ErrorStack::analyze(const Result &result)
{
    set_result(result);
    return analyze();
}

int ErrorStack::print()
{
    if (get_result().ok()) return 0;

    std::ostringstream oss;

    for (auto err_info : get_error_infos())
    {
        oss << *err_info.get();
    }

    m_output = oss.str();
    return 0;
}

const std::string &ErrorStack::get_output() const
{
    return m_output;
}

void ErrorStack::set_result(const Result &result)
{
    m_result = result;
}

const Result &ErrorStack::get_result() const
{
    return m_result;
}

const std::vector<std::shared_ptr<ErrorInfo>> &ErrorStack::get_error_infos() const
{
    return m_error_infos;
}

} // namespace esys::repo
