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
#include "esys/repo/libgit2/guardassign.h"

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
    template<typename T>
    friend int guard_assign(Guard<T> *dest, const Guard<T> &src);

    Guard();
    ~Guard();

    T *get() const;
    T **get_p();

    void reset();

    void operator=(const Guard &other);
    
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

template<typename T>
void Guard<T>::reset()
{
    if (m_data == nullptr) return;

    guard_release<T>(m_data);
    m_data = nullptr;
}

template<typename T>
void Guard<T>::operator=(const Guard &other)
{
    int result = guard_assign<T>(this, other);
    // \TODO throw exception??
}

} // namespace libgit2

} // namespace repo

} // namespace esys
