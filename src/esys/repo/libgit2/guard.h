/*!
 * \file esys/repo/libgit2/gitimpl.h
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
#include "esys/repo/libgit2/guardrelease.h"

namespace esys
{

namespace repo
{

namespace libgit2
{

template<typename T>
class Guard
{
public:
    Guard();
    ~Guard();

    T *get() const;
    T **get_p();

protected:
    T *m_data = nullptr;
};

template<typename T>
Guard<T>::Guard()
{
}

template<typename T>
Guard<T>::~Guard()
{
    guard_release<T>(m_data);
}

template<typename T>
T *Guard<T>::get() const
{
    return m_data;
}

template<typename T>
T **Guard<T>::get_p()
{
    return &m_data;
}

} // namespace libgit2

} // namespace repo

} // namespace esys
