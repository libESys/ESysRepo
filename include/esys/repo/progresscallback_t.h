/*!
 * \file esys/repo/progresscallback_t.h
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
#include "esys/repo/progresscallbackbase.h"

//<swig_inc/>

namespace esys
{

namespace repo
{

template<typename OBJ>
class ProgressCallback_t : public ProgressCallbackBase
{
public:
    typedef void (OBJ::*CallbackType)(const git::Progress &progress);

    ProgressCallback_t();
    ProgressCallback_t(OBJ *callee, CallbackType callback);
    virtual ~ProgressCallback_t();

    void set_callee(OBJ *callee);
    OBJ *get_callee();

    void set_callback(CallbackType callback);
    CallbackType get_callback();

    void git_progress_notif(const git::Progress &progress) override;

protected:
    OBJ *m_callee = nullptr;
    CallbackType m_callback = nullptr;
};

template<typename OBJ>
ProgressCallback_t<OBJ>::ProgressCallback_t()
{
}

template<typename OBJ>
ProgressCallback_t<OBJ>::ProgressCallback_t(OBJ *callee, CallbackType callback)
    : m_callee(callee)
    , m_callback(callback)
{
}

template<typename OBJ>
ProgressCallback_t<OBJ>::~ProgressCallback_t()
{
}

template<typename OBJ>
void ProgressCallback_t<OBJ>::set_callee(OBJ *callee)
{
    m_callee = callee;
}

template<typename OBJ>
OBJ *ProgressCallback_t<OBJ>::get_callee()
{
    return m_callee;
}

template<typename OBJ>
void ProgressCallback_t<OBJ>::set_callback(CallbackType callback)
{
    m_callback = callback;
}

template<typename OBJ>
typename ProgressCallback_t<OBJ>::CallbackType ProgressCallback_t<OBJ>::get_callback()
{
    return m_callback;
}

template<typename OBJ>
void ProgressCallback_t<OBJ>::git_progress_notif(const git::Progress &progress)
{
    if (m_callee == nullptr) return;
    if (m_callback == nullptr) return;

    (m_callee->*m_callback)(progress);
}

} // namespace repo

} // namespace esys
