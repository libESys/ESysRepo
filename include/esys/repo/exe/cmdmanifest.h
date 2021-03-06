/*!
 * \file esys/repo/exe/cmdmanifest.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2021-2022 Michel Gillet
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
#include "esys/repo/exe/cmd.h"
#include "esys/repo/git/commit.h"

#include <memory>
#include <ostream>
#include <vector>

namespace esys::repo::exe
{

/*! \class CmdManifest esys/repo/exe/cmdmanifest.h "esys/repo/exe/cmdmanifest.h"
 * \brief Manifest command
 */
class ESYSREPO_API CmdManifest : public Cmd
{
public:
    //! Default constructor
    CmdManifest();

    //! Destructor
    ~CmdManifest() override;

    void set_revision_as_head(bool revision_as_head);
    bool get_revision_as_head() const;

    void set_output_file(const std::string &output_file);
    const std::string &get_output_file() const;

    Result update_revision_as_head();
    Result update_revision_as_head(std::shared_ptr<manifest::Repository> repo);

protected:
    //!< \cond DOXY_IMPL
    Result impl_run() override;

private:
    bool m_revision_as_head = false;
    std::string m_output_file;
    //!< \endcond
};

} // namespace esys::repo::exe
