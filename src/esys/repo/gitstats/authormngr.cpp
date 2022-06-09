/*!
 * \file esys/repo/gitstats/authormngr.cpp
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
#include "esys/repo/gitstats/authormngr.h"

namespace esys::repo::gitstats
{

AuthorMngr::AuthorMngr() = default;

AuthorMngr::~AuthorMngr() = default;

std::shared_ptr<Author> AuthorMngr::get_author(std::shared_ptr<git::Commit> commit)
{
    auto it = m_authors.find(commit->get_email());

    if (it == m_authors.end()) return nullptr;

    return it->second;
}

std::shared_ptr<Author> AuthorMngr::get_author_or_new(std::shared_ptr<git::Commit> commit)
{
    auto it = m_authors.find(commit->get_email());

    if (it != m_authors.end()) return it->second;

    auto new_author = std::make_shared<Author>();
    new_author->set_email(commit->get_email());
    new_author->set_name(commit->get_author());

    m_authors[commit->get_email()] = new_author;

    return new_author;
}

} // namespace esys::repo::gitstats
