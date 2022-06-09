/*!
 * \file esys/repo/gitstats/datayear.h
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
#include "esys/repo/gitstats/dataperiod.h"

#include <string>
#include <vector>

//<swig_inc/>

namespace esys::repo::gitstats
{

/*! \class Data esys/repo/gitstats/datayear.h "esys/repo/gitstats/datayear.h"
 * \brief
 */
class ESYSREPO_API DataYear
{
public:
    //! Default constructor
    DataYear();

    DataYear(unsigned int year);

    //! Destructor
    ~DataYear();

    void set_year(unsigned int year);
    unsigned int get_year() const;

    std::shared_ptr<DataPeriod> get_week(unsigned int week);
    std::shared_ptr<DataPeriod> get_week_or_new(unsigned int week);
    std::shared_ptr<DataPeriod> get_month(unsigned int month);
    std::shared_ptr<DataPeriod> get_month_or_new(unsigned int month);

    unsigned int get_weeks_with_data_count() const;
    std::shared_ptr<DataPeriod> get_weeks_with_data(unsigned int idx);

private:
    //!< \cond DOXY_IMPL
    unsigned int m_year = 0;
    std::vector<std::shared_ptr<DataPeriod>> m_weeks{52, nullptr};
    std::vector<std::shared_ptr<DataPeriod>> m_months{12, nullptr};
    //!< \endcond
};

} // namespace esys::repo::gitstats
