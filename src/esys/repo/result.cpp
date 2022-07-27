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
    handle_result_code(result_code, file, line_number, function);
}

Result::Result(ResultCode result_code, const std::string &file, int line_number, const std::string &function,
               const std::string &text)
    : m_result_code(result_code)
{
    handle_result_code(result_code, file, line_number, function);

    if (get_error_info() != nullptr)
    {
        auto error_info = get_error_info();
        error_info->set_text(text);
    }
}

Result::Result(ResultCode result_code, const std::string &file, int line_number, const std::string &function,
               int raw_error, const std::string &text)
    : m_result_code(result_code)
{
    handle_result_code(result_code, file, line_number, function);

    if (get_error_info() != nullptr)
    {
        auto error_info = get_error_info();
        error_info->set_raw_error(raw_error);
        error_info->set_text(text);
    }
}

Result::Result(const Result &result, const std::string &file, int line_number, const std::string &function)
{
    handle_result(result, file, line_number, function);
}

Result::Result(const Result &result, const std::string &file, int line_number, const std::string &function,
               const std::string &text)
{
    handle_result(result, file, line_number, function);

    if (get_error_info() != nullptr)
    {
        get_error_info()->set_text(text);
    }
}

Result::Result(const Result &result, ResultCode result_code, const std::string &file, int line_number,
               const std::string &function, const std::string &text)
{
    handle_result(result, file, line_number, function);

    set_result_code(result_code);

    if (get_error_info() != nullptr)
    {
        get_error_info()->set_result_code(result_code);
        get_error_info()->set_text(text);
    }
}

Result::~Result() = default;

void Result::set_result_code(ResultCode result_code)
{
    m_result_code = result_code;
}

void Result::handle_result_code(ResultCode result_code, const std::string &file, int line_number,
                                const std::string &function)
{
    if (result_code != ResultCode::OK)
    {
        auto error_info = std::make_shared<ErrorInfo>();
        error_info->set_file(file);
        error_info->set_line_number(line_number);
        error_info->set_function(function);
        error_info->set_result_code(result_code);
        set_error_info(error_info);
    }
}

void Result::handle_result(const Result &result, const std::string &file, int line_number, const std::string &function)
{
    set_result_code(result.get_result_code());

    handle_result_code(result.get_result_code(), file, line_number, function);

    if (get_error_info() != nullptr)
    {
        auto error_info = get_error_info();
        error_info->set_prev(result.get_error_info());
        error_info->set_index(result.get_error_info()->get_index() + 1);
    }
}

ResultCode Result::get_result_code() const
{
    return m_result_code;
}

int Result::get_result_code_int() const
{
    return static_cast<int>(get_result_code());
}

void Result::set_error_info(std::shared_ptr<ErrorInfo> error_info)
{
    m_error_info = error_info;
}

std::shared_ptr<ErrorInfo> Result::get_error_info()
{
    return m_error_info;
}

void Result::add(const Result &result)
{
    if (result.ok()) return;

    if (get_error_info() == nullptr)
    {
        auto error_info = std::make_shared<ErrorInfo>();
        error_info->set_result_code(ResultCode::ERROR_VECTOR);
        set_error_info(error_info);
    }

    get_error_info()->add_prev(result.get_error_info());
}

const std::shared_ptr<ErrorInfo> Result::get_error_info() const
{
    return m_error_info;
}

bool Result::success() const
{
    return get_result_code() == ResultCode::OK;
}

bool Result::ok() const
{
    return success();
}

bool Result::error() const
{
    return get_result_code() != ResultCode::OK;
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

bool Result::operator==(const ResultCode &result_code)
{
    return get_result_code() == result_code;
}

bool Result::operator!=(const ResultCode &result_code)
{
    return !operator==(result_code);
}

ESYSREPO_API bool operator==(const Result &result, const ResultCode &result_code)
{
    return result.get_result_code() == result_code;
}

ESYSREPO_API bool operator!=(const Result &result, const ResultCode &result_code)
{
    return result.get_result_code() != result_code;
}

ESYSREPO_API bool operator==(const ResultCode &result_code, const Result &result)
{
    return result.get_result_code() == result_code;
}

ESYSREPO_API bool operator!=(const ResultCode &result_code, const Result &result)
{
    return result.get_result_code() != result_code;
}

} // namespace esys::repo

namespace std
{

ESYSREPO_API ostream &operator<<(ostream &os, const esys::repo::Result &result)
{
    return os;
}

} // namespace std
