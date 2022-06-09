/*!
 * \file esys/repo/gitstats/dataperiodauthor.cpp
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
#include "esys/repo/gitstats/dataperiodauthor.h"

namespace esys::repo::gitstats
{

DataPeriodAuthor::DataPeriodAuthor() = default;

DataPeriodAuthor::DataPeriodAuthor(std::shared_ptr<Author> author)
    : m_author(author)
{
}

DataPeriodAuthor::~DataPeriodAuthor() = default;

void DataPeriodAuthor::set_author(std::shared_ptr<Author> author)
{
    m_author = author;
}

std::shared_ptr<Author> DataPeriodAuthor::get_author()
{
    return m_author;
}

const std::shared_ptr<Author> DataPeriodAuthor::get_author() const
{
    return m_author;
}

void DataPeriodAuthor::set_commit_count(unsigned int commit_count)
{
    m_commit_count = commit_count;
}

unsigned int DataPeriodAuthor::get_commit_count() const
{
    return m_commit_count;
}

unsigned int &DataPeriodAuthor::get_commit_count()
{
    return m_commit_count;
}

void DataPeriodAuthor::inc_commit_count()
{
    ++m_commit_count;
}

void DataPeriodAuthor::inc_line_added(unsigned int count)
{
    m_line_added += count;
}

unsigned int DataPeriodAuthor::get_line_added() const
{
    return m_line_added;
}

void DataPeriodAuthor::inc_line_removed(unsigned int count)
{
    m_line_removed += count;
}

unsigned int DataPeriodAuthor::get_line_removed() const
{
    return m_line_removed;
}

void DataPeriodAuthor::inc_renames(unsigned int count)
{
    m_renames += count;
}

unsigned int DataPeriodAuthor::get_renames() const
{
    return m_renames;
}

void DataPeriodAuthor::inc_files_changed(unsigned int count)
{
    m_files_changed += count;
}

unsigned int DataPeriodAuthor::get_files_changed() const
{
    return m_files_changed;
}

} // namespace esys::repo::gitstats
