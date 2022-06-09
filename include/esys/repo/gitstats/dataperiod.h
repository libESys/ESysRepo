/*!
 * \file esys/repo/gitstats/dataperiod.h
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
#include "esys/repo/gitstats/dataperiodauthor.h"

#include <map>
#include <memory>
#include <string>

//<swig_inc/>

namespace esys::repo::gitstats
{

/*! \class Data esys/repo/gitstats/dataperiod.h "esys/repo/gitstats/dataperiod.h"
 * \brief
 */
class ESYSREPO_API DataPeriod
{
public:
    enum class AuthorBy
    {
        NOT_SET,
        NAME,
        EMAIL
    };

    //! Default constructor
    DataPeriod();

    DataPeriod(unsigned int period);

    //! Destructor
    ~DataPeriod();

    void set_period(unsigned int period);
    unsigned int get_period() const;

    void set_author_by(AuthorBy author_by);
    AuthorBy get_author_by() const;

    std::shared_ptr<DataPeriodAuthor> get_author(std::shared_ptr<Author> author);
    std::shared_ptr<DataPeriodAuthor> get_author_or_new(std::shared_ptr<Author> author);

    std::map<std::string, std::shared_ptr<DataPeriodAuthor>> &get_period_author_map();

private:
    //!< \cond DOXY_IMPL
    unsigned int m_period = 0;
    AuthorBy m_author_by = AuthorBy::EMAIL;
    std::map<std::string, std::shared_ptr<DataPeriodAuthor>> m_authors;
    //!< \endcond
};

} // namespace esys::repo::gitstats
