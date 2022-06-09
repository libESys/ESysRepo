/*!
 * \file esys/repo/gitstats/author.cpp
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
#include "esys/repo/gitstats/author.h"

namespace esys::repo::gitstats
{

Author::Author() = default;

Author::~Author() = default;

void Author::set_name(const std::string &name)
{
    m_name = name;
}

const std::string &Author::get_name() const
{
    return m_name;
}

void Author::set_email(const std::string &email)
{
    m_email = email;
}

const std::string &Author::get_email() const
{
    return m_email;
}

} // namespace esys::repo::gitstats
