/*!
 * \file esys/repo/queuemt.h
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

#include <mutex>
#include <deque>
#include <functional>

namespace esys
{

namespace repo
{

/*! \class QueueMT esys/repo/queuemt.h "esys/repo/queuemt.h"
 * \brief Thread-safe queue
 */
template<typename T>
class QueueMT
{
public:
    //! Constructor
    QueueMT();

    //! Destructor
    ~QueueMT();

    //! Push an element at back of the queue
    /*!
     * \param[in] val the element to add to the queue
     */
    void push_back(const T &val);

    //! Push an element at front of the queue
    /*!
     * \param[in] val the element to add to the queue
     */
    void push_front(const T &val);

    //! Pop an element from the back of the queue
    /*!
     * \param[out] val if the queue is not empty, the element at the back of the queue
     * \return 0 if successful, < 0 otherwise
     */
    int pop_back(T &val);

    //! Pop an element from the front of the queue
    /*!
     * \param[out] val if the queue is not empty, the element at the front of the queue
     * \return 0 if successful, < 0 otherwise
     */
    int pop_front(T &val);

    //! Return the size of the queue
    /*!
     * \return the size of the queue
     */
    std::size_t size();

    //! Tells if the queue is empty or not
    /*!
     * \return true if the queue is empty, false otherwise
     */
    bool empty();

    //! Erase elements matching the given condition
    /*!
     * \param[in] fct erase the element if this function return true
     * \return true if the queue is empty, false otherwise
     */
    int remove_if(std::function<bool(const T &val)> fct);

    void for_each(std::function<void(const T &val)> fct);

    void clear();

private:
    //!< \cond DOXY_IMPL
    std::mutex m_mutex;    //!< The mutex to use
    std::deque<T> m_queue; //!< The actual queue
    //!< \endcond
};

template<typename T>
QueueMT<T>::QueueMT()
{
}

template<typename T>
QueueMT<T>::~QueueMT()
{
    m_queue.clear();
}

template<typename T>
void QueueMT<T>::push_back(const T &val)
{
    std::lock_guard lock(m_mutex);

    m_queue.push_back(val);
}

template<typename T>
void QueueMT<T>::push_front(const T &val)
{
    std::lock_guard lock(m_mutex);

    m_queue.push_front(val);
}

template<typename T>
int QueueMT<T>::pop_back(T &val)
{
    std::lock_guard lock(m_mutex);

    val = nullptr;

    if (m_queue.size() == 0) return -1;

    val = m_queue.back();
    m_queue.pop_back();

    return 0;
}

template<typename T>
int QueueMT<T>::pop_front(T &val)
{
    std::lock_guard lock(m_mutex);

    val = nullptr;

    if (m_queue.size() == 0) return -1;

    val = m_queue.front();
    m_queue.pop_front();

    return 0;
}

template<typename T>
std::size_t QueueMT<T>::size()
{
    std::lock_guard lock(m_mutex);

    return m_queue.size();
}

template<typename T>
bool QueueMT<T>::empty()
{
    std::lock_guard lock(m_mutex);

    return m_queue.empty();
}

template<typename T>
int QueueMT<T>::remove_if(std::function<bool(const T &val)> fct)
{
    std::lock_guard lock(m_mutex);

    typename std::deque<T>::iterator it;
    bool remove;
    int result = -1;

    it = m_queue.begin();

    while (it != m_queue.end())
    {
        remove = fct(*it);
        if (remove)
        {
            it = m_queue.erase(it);
            result = 0;
        }
        else
            ++it;
    }
    return result;
}

template<typename T>
void QueueMT<T>::for_each(std::function<void(const T &val)> fct)
{
    std::lock_guard lock(m_mutex);

    for (auto item : m_queue) fct(item);
}

template<typename T>
void QueueMT<T>::clear()
{
    std::lock_guard lock(m_mutex);

    m_queue.clear();
}

} // namespace repo

} // namespace esys
