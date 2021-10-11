/*!
 * \file esys/repo/manifest/base_manifest.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/manifest/base.h"

namespace esys::repo::manifest
{

const std::string Base::s_folder_name = "esysrepo";

const std::string &Base::get_folder_name()
{
    return s_folder_name;
}

Base::Base() = default;

Base::~Base() = default;

} // namespace esys::repo::manifest
