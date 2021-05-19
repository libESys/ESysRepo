/*!
 * \file esys/repo/test/queuemt01.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2021 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/test/esysrepo_t_prec.h"

#include <esys/repo/queuemt.h>

#include <iostream>
#include <sstream>

namespace esys
{

namespace repo
{

namespace test
{

namespace queuemt01
{

class Object
{
public:
    Object();
    Object(int value);

    static std::shared_ptr<Object> new_ptr(int value = 0);

    virtual ~Object();

    int get_id() const;

    void set_value(int value);
    int get_value() const;

protected:
    static int s_count;
    int m_id;
    int m_value = -1;
};

int Object::s_count = 0;

std::shared_ptr<Object> Object::new_ptr(int value)
{
    return std::make_shared<Object>(value);
}

Object::Object()
{
    m_id = s_count;
    ++s_count;
}

Object::Object(int value)
    : m_value(value)
{
    m_id = s_count;
    ++s_count;
}

Object::~Object()
{
}

int Object::get_id() const
{
    return m_id;
}

void Object::set_value(int value)
{
    m_value = value;
}

int Object::get_value() const
{
    return m_value;
}

std::ostream &operator<<(std::ostream &os, const Object &obj)
{
    os << "[" << obj.get_id() << "] " << obj.get_value() << std::endl;
    return os;
}

/*! \class QueueMT01 esys/repo/test/sortbranches01.cpp "esys/repo/test/sortbranches01.cpp"
 *
 *  \brief
 *
 */
ESYSTEST_AUTO_TEST_CASE(QueueMT01)
{
    QueueMT<std::shared_ptr<Object>> queue;
    std::shared_ptr<Object> obj;
    int result;

    ESYSTEST_REQUIRE_EQUAL(queue.size(), 0);

    result = queue.pop_back(obj);
    ESYSTEST_REQUIRE_EQUAL(result, -1);
    ESYSTEST_REQUIRE_EQUAL(obj, nullptr);

    queue.push_back(Object::new_ptr());
    ESYSTEST_REQUIRE_EQUAL(queue.size(), 1);

    queue.push_back(Object::new_ptr());
    ESYSTEST_REQUIRE_EQUAL(queue.size(), 2);

    result = queue.pop_front(obj);
    ESYSTEST_REQUIRE_EQUAL(result, 0);
    ESYSTEST_REQUIRE_EQUAL(queue.size(), 1);
    ESYSTEST_REQUIRE_EQUAL(obj->get_id(), 0);

    queue.push_back(Object::new_ptr());
    ESYSTEST_REQUIRE_EQUAL(queue.size(), 2);

    queue.push_back(Object::new_ptr());
    ESYSTEST_REQUIRE_EQUAL(queue.size(), 3);

    queue.push_back(Object::new_ptr());
    ESYSTEST_REQUIRE_EQUAL(queue.size(), 4);

    int value_int = 2;
    auto erase_fct = [value_int](const std::shared_ptr<Object> &val) { return (val->get_id() == value_int); };
    result = queue.remove_if(erase_fct);
    ESYSTEST_REQUIRE_EQUAL(result, 0);
    ESYSTEST_REQUIRE_EQUAL(queue.size(), 3);

    std::ostringstream oss;
    auto print_fct = [&oss](const std::shared_ptr<Object> &val) { oss << *val; };
    queue.for_each(print_fct);
}

} // namespace queuemt01

} // namespace test

} // namespace repo

} // namespace esys
