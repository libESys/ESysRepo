/*!
 * \file esys/repo/manifest/fetch_manifest.cpp
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
#include "esys/repo/manifest/fetch.h"
#include "esys/repo/manifest/fetchgrepo.h"
#include "esys/repo/manifest/fetchesysrepo.h"
#include "esys/repo/manifest/fetchgitsuper.h"

namespace esys
{

namespace repo
{

namespace manifest
{

Fetch::Fetch()
    : FetchBase()
{
}

Fetch::~Fetch()
{
}

int Fetch::run()
{
    if (get_config_folder() == nullptr) return -1;
    if (get_config_folder()->get_config() == nullptr) return -1;

    switch (get_config_folder()->get_config()->get_manifest_type())
    {
        case manifest::Type::ESYSREPO_MANIFEST: set_fetcher(std::make_shared<FetchESysRepo>()); break;
        case manifest::Type::GIT_SUPER_PROJECT: set_fetcher(std::make_shared<FetchGitSuper>()); break;
        case manifest::Type::GOOGLE_MANIFEST: set_fetcher(std::make_shared<FetchGRepo>()); break;
        default: return -1;
    }

    get_fetcher()->set_config_folder(get_config_folder());
    get_fetcher()->set_manifest(get_manifest());

    return get_fetcher()->run();
}

void Fetch::set_fetcher(std::shared_ptr<FetchBase> fetcher)
{
    m_fetcher = fetcher;
}

std::shared_ptr<FetchBase> Fetch::get_fetcher()
{
    return m_fetcher;
}

const std::shared_ptr<FetchBase> Fetch::get_fetcher() const
{
    return m_fetcher;
}

} // namespace manifest

} // namespace repo

} // namespace esys
