/*!
 * \file esys/repo/git/progress_git.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/git/progress.h"

#include <iomanip>

namespace esys::repo::git
{

Progress::Progress() = default;

void Progress::set_fetch_step(FetchStep fetch_step)
{
    m_fetch_step = fetch_step;
}

FetchStep Progress::get_fetch_step() const
{
    return m_fetch_step;
}

FetchStep &Progress::get_fetch_step()
{
    return m_fetch_step;
}

void Progress::set_percentage(int percentage)
{
    m_percentage = percentage;
}

int Progress::get_percentage() const
{
    return m_percentage;
}

int &Progress::get_percentage()
{
    return m_percentage;
}

void Progress::set_started(bool started)
{
    m_started = started;
}

bool Progress::get_started() const
{
    return m_started;
}

bool &Progress::get_started()
{
    return m_started;
}

void Progress::set_done(bool done)
{
    m_done = done;
}

bool Progress::get_done() const
{
    return m_done;
}

bool &Progress::get_done()
{
    return m_done;
}

void Progress::print(std::ostream &os)
{
    os << "[";
}

void Progress::print(std::ostream &os, int id)
{
    os << "[" << std::setw(2) << id << ": ";

    switch (get_fetch_step())
    {
        case FetchStep::NOT_SET: os << "0"; break;
        case FetchStep::ENUMERATING: os << "1"; break;
        case FetchStep::COUNTING: os << "2"; break;
        case FetchStep::COMPRESSING: os << "3"; break;
        case FetchStep::TOTAL: os << "4"; break;
        case FetchStep::RECEIVING: os << "5"; break;
        case FetchStep::RESOLVING: os << "6"; break;
        default: os << "?"; break;
    }
    os << "/6 ";
    if ((m_done) || (get_percentage() == MAX_PERCENTAGE) || (get_percentage() < 0))
        os << "  ";
    else
        os << std::setw(2) << get_percentage();
    os << "]";
}

} // namespace esys::repo::git
