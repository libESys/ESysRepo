/*!
 * \file esys/repo/git/commit.cpp
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
#include "esys/repo/git/commit.h"

namespace esys::repo::git
{

Commit::Commit()
{
}

Commit::~Commit()
{
}

void Commit::set_hash(const std::string &hash)
{
    get_hash().set_hash(hash);
}

const CommitHash &Commit::get_hash() const
{
    return m_hash;
}

CommitHash &Commit::get_hash()
{
    return m_hash;
}

void Commit::set_message(const std::string &message)
{
    m_message = message;
}

const std::string &Commit::get_message() const
{
    return m_message;
}

void Commit::set_author(const std::string &author)
{
    m_author = author;
}

const std::string &Commit::get_author() const
{
    return m_author;
}

void Commit::set_email(const std::string &email)
{
    m_email = email;
}

const std::string &Commit::get_email() const
{
    return m_email;
}

void Commit::set_date_time(const std::chrono::system_clock::time_point &date_time)
{
    m_date_time = date_time;
}

const std::chrono::system_clock::time_point &Commit::get_date_time() const
{
    return m_date_time;
}

} // namespace esys::repo::git
