/*!
 * \file esys/repo/gitstats/data.cpp
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
#include "esys/repo/gitstats/data.h"

namespace esys::repo::gitstats
{

Data::Data() = default;

Data::~Data() = default;

std::shared_ptr<DataYear> Data::get_year(unsigned int year)
{
    auto it = m_year_map.find(year);

    if (it == m_year_map.end()) return nullptr;

    return it->second;
}

std::shared_ptr<DataYear> Data::get_year_or_new(unsigned int year)
{
    auto it = m_year_map.find(year);

    if (it != m_year_map.end()) return it->second;

    auto year_p = std::make_shared<DataYear>(year);
    m_year_map[year] = year_p;

    return year_p;
}

std::map<unsigned int, std::shared_ptr<DataYear>> &Data::get_year_map()
{
    return m_year_map;
}

const std::map<unsigned int, std::shared_ptr<DataYear>> &Data::get_year_map() const
{
    return m_year_map;
}

} // namespace esys::repo::gitstats
