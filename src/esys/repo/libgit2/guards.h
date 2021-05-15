/*!
 * \file esys/repo/libgit2/guards.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2021 Michel Gillet
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
#include "esys/repo/libgit2/guardsrelease.h"

namespace esys
{

namespace repo
{

namespace libgit2
{

template<typename T>
class GuardS
{
public:
    GuardS();
    ~GuardS();

    const T *get() const;
    T *get();
    
protected:
    T m_data = {0};
};

template<typename T>
GuardS<T>::GuardS()
{
}

template<typename T>
GuardS<T>::~GuardS()
{
    guards_release<T>(&m_data);
}

template<typename T>
const T *GuardS<T>::get() const
{
    return &m_data;
}

template<typename T>
T *GuardS<T>::get()
{
    return &m_data;
}

} // namespace libgit2

} // namespace repo

} // namespace esys
