/*!
 * \file esys/repo/manifest/jsonfile.h
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
#include "esys/repo/manifest.h"
#include "esys/repo/manifest/file.h"

#include <memory>

namespace esys
{

namespace repo
{

namespace manifest
{

class ESYSREPO_API JSONFile : public File
{
public:
    JSONFile();
    virtual ~JSONFile();

    int read(const std::string &path) override;
    int write(const std::string &path) override;

protected:
};

} // namespace manifest

} // namespace repo

} // namespace esys
