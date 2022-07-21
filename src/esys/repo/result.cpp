/*!
 * \file esys/repo/result.cpp
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
#include "esys/repo/result.h"

namespace esys::repo
{

Result::Result() = default;

Result::Result(const Result &result)
{
    set_result_code(result.get_result_code());
    set_error_info(result.get_error_info());
}

Result::Result(ResultCode result_code, const std::string &file, int line_number, const std::string &function)
    : m_result_code(result_code)
{
    if (result_code != ResultCode::SUCCESS)
    {
        auto error_info = std::make_shared<ErrorInfo>();
        error_info->set_file(file);
        error_info->set_line_number(line_number);
        error_info->set_function(function);
        error_info->set_result_code(result_code);
        set_error_info(error_info);
    }
}

Result::Result(const Result &result, const std::string &file, int line_number, const std::string &function)
{
    set_result_code(result.get_result_code());

    if (get_result_code() != ResultCode::SUCCESS)
    {
        auto error_info = std::make_shared<ErrorInfo>();
        error_info->set_file(file);
        error_info->set_line_number(line_number);
        error_info->set_function(function);
        error_info->set_prev(result.get_error_info());
        error_info->set_index(result.get_error_info()->get_index() + 1);
        set_error_info(error_info);
    }
}

Result::~Result() = default;

void Result::set_result_code(ResultCode result_code)
{
    m_result_code = result_code;
}

ResultCode Result::get_result_code() const
{
    return m_result_code;
}

void Result::set_error_info(std::shared_ptr<ErrorInfo> error_info)
{
    m_error_info = error_info;
}

std::shared_ptr<ErrorInfo> Result::get_error_info()
{
    return m_error_info;
}

const std::shared_ptr<ErrorInfo> Result::get_error_info() const
{
    return m_error_info;
}

bool Result::success()
{
    return get_result_code() == ResultCode::SUCCESS;
}

bool Result::error()
{
    return get_result_code() != ResultCode::SUCCESS;
}

Result::operator ResultCode() const
{
    return get_result_code();
}

Result &Result::operator=(const Result &other)
{
    if (&other == this) return *this;

    set_result_code(other.get_result_code());
    set_error_info(other.get_error_info());
    return *this;
}

} // namespace esys::repo

namespace std
{

ESYSREPO_API ostream &operator<<(ostream &os, const esys::repo::Result &result)
{
    return os;
}

}
