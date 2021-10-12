/*!
 * \file esys/repo/manifest/task_t.h
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
#include "esys/repo/manifest/taskbase.h"

#include <memory>
#include <functional>

namespace esys
{

namespace repo
{

namespace manifest
{

template<typename OBJ, typename F, typename... ARGS>
class Task_t : public TaskBase
{
public:
    Task_t(std::shared_ptr<OBJ> obj, F &&raw_fct, ARGS &&... args);
    Task_t(std::shared_ptr<OBJ> obj, F &&raw_fct, std::shared_ptr<Repository> repo, ARGS &&... args);

    ~Task_t() override;

    int run() override;

private:
    std::shared_ptr<OBJ> m_obj;
    F m_raw_fct;
    std::function<int()> m_fct;
};

template<typename OBJ, typename F, typename... ARGS>
Task_t<OBJ, F, ARGS...>::Task_t(std::shared_ptr<OBJ> obj, F &&raw_fct, ARGS &&... args)
    : TaskBase()
    , m_obj(obj)
    , m_raw_fct(std::forward<F>(raw_fct))
{
    m_fct = [obj, raw_fct, args...] { return (obj.get()->*raw_fct)(args...); };
}

template<typename OBJ, typename F, typename... ARGS>
Task_t<OBJ, F, ARGS...>::Task_t(std::shared_ptr<OBJ> obj, F &&raw_fct, std::shared_ptr<Repository> repo,
                                ARGS &&... args)
    : TaskBase()
    , m_obj(obj)
    , m_raw_fct(std::forward<F>(raw_fct))
{
    this->set_repo(repo);

    m_fct = [obj, raw_fct, repo, args...] { return (obj.get()->*raw_fct)(repo, args...); };
}

template<typename OBJ, typename F, typename... ARGS>
Task_t<OBJ, F, ARGS...>::~Task_t()
{
}

template<typename OBJ, typename F, typename... ARGS>
int Task_t<OBJ, F, ARGS...>::run()
{
    int result = m_fct();
    this->set_result(result);

    return result;
}

} // namespace manifest

} // namespace repo

} // namespace esys
