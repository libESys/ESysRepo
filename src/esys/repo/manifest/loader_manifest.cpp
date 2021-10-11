/*!
 * \file esys/repo/manifest/loader_manifest.cpp
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
#include "esys/repo/manifest/loader.h"
#include "esys/repo/manifest/loadergrepo.h"
#include "esys/repo/manifest/loaderesysrepo.h"
#include "esys/repo/manifest/loadergitsuper.h"

namespace esys::repo::manifest
{

Loader::Loader() = default;

Loader::~Loader() = default;

int Loader::run()
{
    if (get_config_folder() == nullptr) return -1;
    if (get_config_folder()->get_config() == nullptr) return -1;

    switch (get_config_folder()->get_config()->get_manifest_type())
    {
        case manifest::Type::ESYSREPO_MANIFEST: set_loader(std::make_shared<LoaderESysRepo>()); break;
        case manifest::Type::GIT_SUPER_PROJECT: set_loader(std::make_shared<LoaderGitSuper>()); break;
        case manifest::Type::GOOGLE_MANIFEST: set_loader(std::make_shared<LoaderGRepo>()); break;
        default: return -1;
    }

    get_loader()->set_config_folder(get_config_folder());
    get_loader()->set_manifest(get_manifest());
    get_loader()->set_logger_if(get_logger_if());
    return get_loader()->run();
}

void Loader::set_loader(std::shared_ptr<LoaderBase> loader)
{
    m_loader = loader;
}

std::shared_ptr<LoaderBase> Loader::get_loader()
{
    return m_loader;
}

const std::shared_ptr<LoaderBase> Loader::get_loader() const
{
    return m_loader;
}

} // namespace esys::repo::manifest
