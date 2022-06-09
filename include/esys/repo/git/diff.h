/*!
 * \file esys/repo/git/diff.h
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
#include "esys/repo/git/filemode.h"

#include <string>
#include <memory>
#include <vector>

//<swig_inc/>

namespace esys::repo::git
{

/*! \class Diff esys/repo/git/diff.h "esys/repo/git/diff.h"
 * \brief
 */
class ESYSREPO_API Diff
{
public:
    //! Default constructor
    Diff();

    //! Destructor
    ~Diff();

    void set_files_changed(unsigned int files_changed);
    unsigned int get_files_changed() const;

    void set_insertions(unsigned int insertions);
    unsigned int get_insertions() const;

    void set_deletions(unsigned int deletions);
    unsigned int get_deletions() const;

    void set_renames(unsigned int renames);
    unsigned int get_renames() const;

private:
    //!< \cond DOXY_IMPL
    unsigned int m_files_changed = 0;
    unsigned int m_insertions = 0;
    unsigned int m_deletions = 0;
    unsigned int m_renames = 0;
    //!< \endcond
};

} // namespace esys::repo::git
