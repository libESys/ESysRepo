/*!
 * \file esys/repo/resultcode.cpp
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
#include "esys/repo/resultcode.h"

namespace std
{

ESYSREPO_API ostream &operator<<(ostream &os, const esys::repo::ResultCode &result)
{
    return os;
}

} // namespace std
