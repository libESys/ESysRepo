/*!
 * \file esys/repo/git/progress.h
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
#include "esys/repo/git/fetchstep.h"

#include <ostream>
#include <cstddef>

//<swig_inc/>

namespace esys
{

namespace repo
{

namespace git
{

class ESYSREPO_API Progress
{
public:
    static const int MAX_PERCENTAGE = 100;

    Progress();

    void set_fetch_step(FetchStep fetch_step);
    FetchStep get_fetch_step() const;
    FetchStep &get_fetch_step();

    void set_percentage(int percentage);
    int get_percentage() const;
    int &get_percentage();

    void set_started(bool started);
    bool get_started() const;
    bool &get_started();

    void set_done(bool done);
    bool get_done() const;
    bool &get_done();

    void print(std::ostream &os);
    void print(std::ostream &os, int id);

private:
    FetchStep m_fetch_step = FetchStep::NOT_SET;
    int m_percentage = -1;
    bool m_done = false;
    bool m_started = false;
};

} // namespace git

} // namespace repo

} // namespace esys
