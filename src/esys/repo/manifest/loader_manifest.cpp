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
    manifest::Type manifest_type = manifest::Type::NOT_SET;
    std::shared_ptr<Config> config;

    config = get_config();
    if (config != nullptr)
    {
        manifest_type = config->get_manifest_type();
    }
    else if (get_config_folder() != nullptr)
    {
        config = get_config_folder()->get_config();
        if (config == nullptr) return -1;
        manifest_type = config->get_manifest_type();
    }
    else
        return -2;

    switch (manifest_type)
    {
        case manifest::Type::ESYSREPO_MANIFEST: set_loader(std::make_shared<LoaderESysRepo>()); break;
        case manifest::Type::GIT_SUPER_PROJECT: set_loader(std::make_shared<LoaderGitSuper>()); break;
        case manifest::Type::GOOGLE_MANIFEST:
        case manifest::Type::RAW_GOOGLE_MANIFEST: set_loader(std::make_shared<LoaderGRepo>()); break;
        default: return -1;
    }

    get_loader()->set_config(config);
    get_loader()->set_config_folder(get_config_folder());
    get_loader()->set_manifest(LoaderBase::get_manifest());
    get_loader()->set_logger_if(get_logger_if());
    return get_loader()->run();
}

void Loader::set_loader(std::shared_ptr<LoaderBase> loader)
{
    m_loader = loader;
}

std::shared_ptr<LoaderBase> Loader::get_loader() const
{
    return m_loader;
}

std::shared_ptr<Manifest> Loader::get_manifest() const
{
    if (get_loader() == nullptr) return nullptr;
    return get_loader()->get_manifest();
}

} // namespace esys::repo::manifest
