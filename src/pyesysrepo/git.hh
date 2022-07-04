// PySwig 0.1.0

/*!
 * \file esys/repo/git.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2021 Michel Gillet
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

#ifndef ESYSREPO_USE_LIBGIT2
#define ESYSREPO_USE_LIBGIT2 1
#endif

#include "esys/repo/libgit2/git.h"

//<swig_inc>
%{
#include "esys/repo/git.h"
%}
//</swig_inc>
