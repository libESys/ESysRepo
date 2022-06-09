/*!
 * \file esys/repo/gitstats/basic.h
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
#include "esys/repo/gitstats/data.h"
#include "esys/repo/gitstats/authormngr.h"

#include "esys/repo/git/walkcommit.h"

#include <memory>

//<swig_inc/>

namespace esys::repo::gitstats
{

/*! \class Basic esys/repo/gitstats/basic.h "esys/repo/gitstats/basic.h"
 * \brief Basic stats
 */
class ESYSREPO_API Basic : public git::WalkCommit
{
public:
    //! Default constructor
    Basic();

    //! Constructor
    Basic(std::shared_ptr<Data> data);

    //! Destructor
    ~Basic();

    void set_data(std::shared_ptr<Data> data);
    std::shared_ptr<Data> get_data();
    std::shared_ptr<Data> get_data_or_new();

    void set_author_mngr(std::shared_ptr<AuthorMngr> author_mngr);
    std::shared_ptr<AuthorMngr> get_author_mngr();
    std::shared_ptr<AuthorMngr> get_author_mngr_or_new();

    int new_commit(GitBase *git_base, std::shared_ptr<git::Commit> commit) override;

private:
    //!< \cond DOXY_IMPL
    std::shared_ptr<Data> m_data;
    bool m_period_per_week = true;
    std::shared_ptr<AuthorMngr> m_author_mngr;
    //!< \endcond
};

} // namespace esys::repo::gitstats
