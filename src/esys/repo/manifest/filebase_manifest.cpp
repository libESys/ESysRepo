/*!
 * \file esys/repo/manifest/filebase_manifest.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/manifest/filebase.h"

namespace esys::repo::manifest
{

FileBase::FileBase() = default;

FileBase::~FileBase() = default;

void FileBase::set_data(std::shared_ptr<Manifest> data)
{
    m_data = data;
}

std::shared_ptr<Manifest> FileBase::get_data()
{
    return m_data;
}

const std::shared_ptr<Manifest> FileBase::get_data() const
{
    return m_data;
}

std::vector<std::shared_ptr<FileError>> &FileBase::get_errors()
{
    return m_errors;
}

const std::vector<std::shared_ptr<FileError>> &FileBase::get_errors() const
{
    return m_errors;
}

void FileBase::add_error(std::shared_ptr<FileError> error)
{
    m_errors.push_back(error);
}

void FileBase::add_error(int value, const std::string &msg)
{
    add_error(value, msg, -1);
}

void FileBase::add_error(int value, const std::string &msg, int line_number)
{
    auto error = std::make_shared<FileError>();
    error->set_value(value);
    error->set_msg(msg);
    error->set_line_number(line_number);

    m_errors.push_back(error);
}

} // namespace esys::repo::manifest
