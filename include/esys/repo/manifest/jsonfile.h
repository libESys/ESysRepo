/*!
 * \file esys/repo/manifest/jsonfile.h
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

/*! \class JSONFile esys/repo/manifest/jsonfile.h "esys/repo/manifest/jsonfile.h"
 * \brief Read and write the ESysRepo manifest in JSON format
 */
class ESYSREPO_API JSONFile : public File
{
public:
    //! Default constructor
    JSONFile();

    //! Destructor
    virtual ~JSONFile();

    int read(const std::string &path) override;
    int write(const std::string &path) override;
    int write(std::ostream &os) override;

protected:
};

} // namespace manifest

} // namespace repo

} // namespace esys
