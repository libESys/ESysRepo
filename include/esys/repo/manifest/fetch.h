/*!
 * \file esys/repo/manifest/fetch.h
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
#include "esys/repo/manifest/fetchbase.h"

#include <memory>

namespace esys
{

namespace repo
{

namespace manifest
{

class ESYSREPO_API Fetch : public FetchBase
{
public:
    Fetch();
    virtual ~Fetch();

    int run() override;

    void set_fetcher(std::shared_ptr<FetchBase> fetcher);
    std::shared_ptr<FetchBase> get_fetcher();
    const std::shared_ptr<FetchBase> get_fetcher() const;

protected:
    std::shared_ptr<FetchBase> m_fetcher;

};

} // namespace manifest

} // namespace repo

} // namespace esys
