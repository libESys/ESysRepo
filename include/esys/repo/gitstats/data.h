/*!
 * \file esys/repo/gitstats/data.h
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
#include "esys/repo/gitstats/datayear.h"

#include <map>
#include <memory>
#include <string>

//<swig_inc/>

namespace esys::repo::gitstats
{

/*! \class Data esys/repo/gitstats/data.h "esys/repo/gitstats/data.h"
 * \brief
 */
class ESYSREPO_API Data
{
public:
    //! Default constructor
    Data();

    //! Destructor
    ~Data();

    std::shared_ptr<DataYear> get_year(unsigned int year);
    std::shared_ptr<DataYear> get_year_or_new(unsigned int year);
    std::map<unsigned int, std::shared_ptr<DataYear>> &get_year_map();
    const std::map<unsigned int, std::shared_ptr<DataYear>> &get_year_map() const;

private:
    //!< \cond DOXY_IMPL
    std::map<unsigned int, std::shared_ptr<DataYear>> m_year_map;
    //!< \endcond
};

} // namespace esys::repo::gitstats
