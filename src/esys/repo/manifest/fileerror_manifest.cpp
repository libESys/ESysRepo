/*!
 * \file esys/repo/manifest/fileerror.cpp
 * \brief
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/manifest/fileerror.h"

namespace esys
{

namespace repo
{

namespace manifest
{

FileError::FileError()
{
}

FileError::~FileError()
{
}


void FileError::set_msg(const std::string &msg)
{
    m_msg = msg;
}


const std::string &FileError::get_msg()
{
    return m_msg;
}


void FileError::set_value(int value)
{
    m_value = value;
}


int FileError::get_value() const
{
    return m_value;
}


void FileError::set_line_number(int line_number)
{
    m_line_number = line_number;
}


int FileError::get_line_number() const
{
    return m_line_number;
}



} // namespace repo

} // namespace esys

} // namespace esys
