/*!
 * \file esys/repo/gitstats/dataperiod.cpp
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
#include "esys/repo/gitstats/dataperiod.h"

namespace esys::repo::gitstats
{

DataPeriod::DataPeriod() = default;

DataPeriod::DataPeriod(unsigned int period)
    : m_period(period)
{
}

DataPeriod::~DataPeriod() = default;

void DataPeriod::set_period(unsigned int period)
{
    m_period = period;
}

unsigned int DataPeriod::get_period() const
{
    return m_period;
}

void DataPeriod::set_author_by(AuthorBy author_by)
{
    m_author_by = author_by;
}

DataPeriod::AuthorBy DataPeriod::get_author_by() const
{
    return m_author_by;
}

std::shared_ptr<DataPeriodAuthor> DataPeriod::get_author(std::shared_ptr<Author> author)
{
    std::string key;

    switch (get_author_by())
    {
        case AuthorBy::NOT_SET: return nullptr;
        case AuthorBy::EMAIL: key = author->get_email(); break;
        case AuthorBy::NAME: key = author->get_name(); break;
        default: return nullptr;
    }
    auto it = m_authors.find(key);
    if (it == m_authors.end()) return nullptr;
    return it->second;
}

std::shared_ptr<DataPeriodAuthor> DataPeriod::get_author_or_new(std::shared_ptr<Author> author)
{
    auto result = get_author(author);

    if (result != nullptr) return result;

    std::string key;

    switch (get_author_by())
    {
        case AuthorBy::NOT_SET: return nullptr;
        case AuthorBy::EMAIL: key = author->get_email(); break;
        case AuthorBy::NAME: key = author->get_name(); break;
        default: return nullptr;
    }

    auto new_data = std::make_shared<DataPeriodAuthor>(author);
    m_authors[key] = new_data;
    return new_data;
}

std::map<std::string, std::shared_ptr<DataPeriodAuthor>> &DataPeriod::get_period_author_map()
{
    return m_authors;
}

} // namespace esys::repo::gitstats
