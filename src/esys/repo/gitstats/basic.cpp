/*!
 * \file esys/repo/gitstats/basic.cpp
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
#include "esys/repo/gitstats/basic.h"
#include "esys/repo/gitbase.h"
#include "esys/repo/git/diff.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace esys::repo::gitstats
{

Basic::Basic() = default;

Basic::Basic(std::shared_ptr<Data> data)
    : m_data(data)
{
}

Basic::~Basic() = default;

void Basic::set_data(std::shared_ptr<Data> data)
{
    m_data = data;
}

std::shared_ptr<Data> Basic::get_data()
{
    return m_data;
}

std::shared_ptr<Data> Basic::get_data_or_new()
{
    if (m_data == nullptr) m_data = std::make_shared<Data>();

    return m_data;
}

void Basic::set_author_mngr(std::shared_ptr<AuthorMngr> author_mngr)
{
    m_author_mngr = author_mngr;
}

std::shared_ptr<AuthorMngr> Basic::get_author_mngr()
{
    return m_author_mngr;
}

std::shared_ptr<AuthorMngr> Basic::get_author_mngr_or_new()
{
    if (m_author_mngr == nullptr) m_author_mngr = std::make_shared<AuthorMngr>();

    return m_author_mngr;
}

int Basic::new_commit(GitBase *git_base, std::shared_ptr<git::Commit> commit)
{
    auto date_time = commit->get_date_time();

    boost::gregorian::date date =
        boost::posix_time::from_time_t(std::chrono::system_clock::to_time_t(date_time)).date();

    auto data_year = get_data_or_new()->get_year_or_new(date.year());
    std::shared_ptr<DataPeriod> data_period;
    std::shared_ptr<DataPeriodAuthor> data_period_author;

    auto author = get_author_mngr_or_new()->get_author_or_new(commit);

    data_period = data_year->get_week_or_new(date.week_number() - 1);

    data_period_author = data_period->get_author_or_new(author);
    data_period_author->inc_commit_count();

    std::shared_ptr<git::Diff> diff = std::make_shared<git::Diff>();
    int result = git_base->diff(commit->get_hash(), diff);
    if (result < 0) return -1;

    data_period_author->inc_line_added(diff.get()->get_insertions());
    data_period_author->inc_line_removed(diff.get()->get_deletions());
    data_period_author->inc_renames(diff.get()->get_renames());
    data_period_author->inc_files_changed(diff.get()->get_files_changed());
    return 0;
}

} // namespace esys::repo::gitstats
