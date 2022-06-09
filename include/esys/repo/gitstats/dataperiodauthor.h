/*!
 * \file esys/repo/gitstats/dataperiodauthor.h
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
#include "esys/repo/gitstats/author.h"

#include <map>
#include <string>

//<swig_inc/>

namespace esys::repo::gitstats
{

/*! \class DataPeriodAuthor esys/repo/gitstats/dataperiodauthor.h "esys/repo/gitstats/dataperiodauthor.h"
 * \brief
 */
class ESYSREPO_API DataPeriodAuthor
{
public:
    //! Default constructor
    DataPeriodAuthor();

    //! Constructor
    DataPeriodAuthor(std::shared_ptr<Author>);

    //! Destructor
    ~DataPeriodAuthor();

    void set_author(std::shared_ptr<Author> author);
    std::shared_ptr<Author> get_author();
    const std::shared_ptr<Author> get_author() const;

    void set_commit_count(unsigned int commit_count);
    unsigned int get_commit_count() const;
    unsigned int &get_commit_count();
    void inc_commit_count();

    void inc_line_added(unsigned int count);
    unsigned int get_line_added() const;

    void inc_line_removed(unsigned int count);
    unsigned int get_line_removed() const;

    void inc_renames(unsigned int count);
    unsigned int get_renames() const;

    void inc_files_changed(unsigned int count);
    unsigned int get_files_changed() const;

private:
    //!< \cond DOXY_IMPL
    std::shared_ptr<Author> m_author;
    unsigned int m_commit_count = 0;
    unsigned int m_line_added = 0;
    unsigned int m_line_removed = 0;
    unsigned int m_renames = 0;
    unsigned int m_files_changed = 0;
    //!< \endcond
};

} // namespace esys::repo::gitstats
