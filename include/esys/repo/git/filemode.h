/*!
 * \file esys/repo/git/filemode.h
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

//<swig_inc/>

namespace esys::repo::git
{

enum class FileMode
{
    NOT_SET,
    NEW,
    TREE,
    BLOB,            //!< Normal file
    BLOB_EXECUTABLE, //!< Executable file,
    LINK,
    COMMIT,

};

} // namespace esys::repo::git
