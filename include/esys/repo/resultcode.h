/*!
 * \file esys/repo/resultcode.h
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

#include <ostream>

namespace esys::repo
{

enum class ResultCode
{
    SUCCESS = 0,
    GENERIC_ERROR = -1,
};

}

namespace std
{

ESYSREPO_API ostream &operator<<(ostream &os, const esys::repo::ResultCode &result); //<swig_out/>

}
