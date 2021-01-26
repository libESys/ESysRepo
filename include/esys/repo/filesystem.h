/*!
 * \file esys/repo/filesystem.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020 Michel Gillet
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

#include <string>

namespace esys
{

namespace repo
{

namespace stdcpp
{

ESYSREPO_API int copy(const std::string &src, const std::string &dst, bool recursive = false);
ESYSREPO_API int remove_all(const std::string &path);

} // namespace stdcpp

#ifdef ESYSREPO_USE_STD_FILESYSTEM
using namespace stdcpp;
#endif

namespace boost_no_recur
{

ESYSREPO_API int copy(const std::string &src, const std::string &dst, bool recursive = false);

}

#ifdef ESYSREPO_USE_BOOST_FILESYSTEM_NO_RECURSIVE
using namespace boost_no_recur;
#endif

namespace boost_recur
{

ESYSREPO_API int copy(const std::string &src, const std::string &dst, bool recursive = false);

}

#ifdef ESYSREPO_USE_BOOST_FILESYSTEM
using namespace boost_recur;
#endif

namespace boost_all
{

ESYSREPO_API int remove_all(const std::string &path);

}

namespace boost_no_all
{

ESYSREPO_API int remove_all(const std::string &path);
ESYSREPO_API int move(const std::string &src, const std::string &dst, bool recursive = false);

} // namespace boost_no_all

#if defined(ESYSREPO_USE_BOOST_FILESYSTEM) || defined(ESYSREPO_USE_BOOST_FILESYSTEM_NO_RECURSIVE)
using namespace boost_all;
#endif

ESYSREPO_API int move(const std::string &src, const std::string &dst, bool recursive = false);

} // namespace repo

} // namespace esys
