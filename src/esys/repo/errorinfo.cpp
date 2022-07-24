/*!
 * \file esys/repo/errorinfo.cpp
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
#include "esys/repo/errorinfo.h"

namespace esys::repo
{

ErrorInfo::ErrorInfo() = default;

ErrorInfo::~ErrorInfo() = default;

void ErrorInfo::set_index(int index)
{
    m_index = index;
}

int ErrorInfo::get_index() const
{
    return m_index;
}

void ErrorInfo::set_result_code(ResultCode result_code)
{
    m_result_code = result_code;
}

ResultCode ErrorInfo::get_result_code() const
{
    return m_result_code;
}

int ErrorInfo::get_result_code_int() const
{
    return static_cast<int>(m_result_code);
}

void ErrorInfo::set_raw_error(int raw_error)
{
    m_raw_error = raw_error;
}


int ErrorInfo::get_raw_error() const
{
    return m_raw_error;
}

void ErrorInfo::set_file(const std::string &file)
{
    m_file = file;
}

const std::string &ErrorInfo::get_file() const
{
    return m_file;
}

void ErrorInfo::set_line_number(int line_number)
{
    m_line_number = line_number;
}

int ErrorInfo::get_line_number() const
{
    return m_line_number;
}

void ErrorInfo::set_function(const std::string &function)
{
    m_function = function;
}

const std::string &ErrorInfo::get_function() const
{
    return m_function;
}

void ErrorInfo::set_text(const std::string &text)
{
    m_text = text;
}

const std::string &ErrorInfo::get_text() const
{
    return m_text;
}

void ErrorInfo::set_prev(std::shared_ptr<ErrorInfo> prev)
{
    m_prev = prev;
}

std::shared_ptr<ErrorInfo> ErrorInfo::get_prev()
{
    return m_prev;
}

void ErrorInfo::print(std::ostream &os) const
{
    std::string name = ResultCode::s_find_name(get_result_code());

    os << "[" << get_index() << "] ";
    if (!name.empty()) os << name << "(" << get_result_code_int() << ")" << std::endl;

    os << "    file : " << get_file() << std::endl;
    os << "    line : " << get_line_number() << std::endl;
    os << "    fct  : " << get_function() << std::endl;
    os << "    text : " << get_text() << std::endl;
    os << "    err  : " << get_raw_error() << std::endl;

}

} // namespace esys::repo

namespace std
{

ESYSREPO_API ostream &operator<<(ostream &os, const esys::repo::ErrorInfo &error_info)
{
    error_info.print(os);

    return os;
}

} // namespace std
