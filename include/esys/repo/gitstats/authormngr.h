/*!
 * \file esys/repo/gitstats/authormngr.h
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

#pragma once

#include "esys/repo/esysrepo_defs.h"
#include "esys/repo/gitstats/author.h"

#include "esys/repo/git/commit.h"

#include <map>
#include <string>

//<swig_inc/>

namespace esys::repo::gitstats
{

/*! \class AuthorMngr esys/repo/gitstats/authormngr.h "esys/repo/gitstats/authormngr.h"
 * \brief
 */
class ESYSREPO_API AuthorMngr
{
public:
    //! Default constructor
    AuthorMngr();

    //! Destructor
    ~AuthorMngr();

    std::shared_ptr<Author> get_author(std::shared_ptr<git::Commit> commit);
    std::shared_ptr<Author> get_author_or_new(std::shared_ptr<git::Commit> commit);

private:
    //!< \cond DOXY_IMPL
    std::map<std::string, std::shared_ptr<Author>> m_authors; //!< The authors

    //!< \endcond
};

} // namespace esys::repo::gitstats
