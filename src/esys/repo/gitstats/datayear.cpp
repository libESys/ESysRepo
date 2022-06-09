/*!
 * \file esys/repo/gitstats/datayear.cpp
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
#include "esys/repo/gitstats/datayear.h"

#include <cassert>

namespace esys::repo::gitstats
{

DataYear::DataYear() = default;

DataYear::DataYear(unsigned int year)
    : m_year(year)
{
}

DataYear::~DataYear() = default;

void DataYear::set_year(unsigned int year)
{
    m_year = year;
}

unsigned int DataYear::get_year() const
{
    return m_year;
}

std::shared_ptr<DataPeriod> DataYear::get_week(unsigned int week)
{
    assert(week < 52);

    return m_weeks[week];
}

std::shared_ptr<DataPeriod> DataYear::get_week_or_new(unsigned int week)
{
    assert(week < 52);

    if (m_weeks[week] == nullptr) m_weeks[week] = std::make_shared<DataPeriod>(week);

    return m_weeks[week];
}

std::shared_ptr<DataPeriod> DataYear::get_month(unsigned int month)
{
    assert(month < 12);

    return m_months[month];
}

std::shared_ptr<DataPeriod> DataYear::get_month_or_new(unsigned int month)
{
    assert(month < 12);

    if (m_months[month] == nullptr) m_months[month] = std::make_shared<DataPeriod>(month);

    return m_months[month];
}

unsigned int DataYear::get_weeks_with_data_count() const
{
    unsigned int count = 0;

    for (auto week : m_weeks)
    {
        if (week != nullptr) ++count;
    }

    return count;
}

std::shared_ptr<DataPeriod> DataYear::get_weeks_with_data(unsigned int idx)
{
    unsigned int count = 0;

    for (auto week : m_weeks)
    {
        if (week != nullptr)
        {
            if (count == idx) return week;
            ++count;
        }
    }
    return nullptr;
}

} // namespace esys::repo::gitstats
