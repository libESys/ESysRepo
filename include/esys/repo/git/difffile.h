/*!
 * \file esys/repo/git/difffile.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2022 Michel Gillet
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
#include "esys/repo/git/filemode.h"

#include <string>
#include <memory>
#include <vector>

//<swig_inc/>

namespace esys::repo::git
{

/*! \class DiffFile esys/repo/git/difffile.h "esys/repo/git/difffile.h"
 * \brief
 */
class ESYSREPO_API DiffFile
{
public:
    //! Default constructor
    DiffFile();

    //! Destructor
    virtual ~DiffFile();

    void set_id(const std::string &id);
    std::string &get_id();
    const std::string &get_id() const;

    void set_path(const std::string &path);
    std::string &get_path();
    const std::string &get_path() const;

    void set_size(uint64_t size);
    uint64_t &get_size();
    uint64_t get_size() const;

    void set_mode(FileMode file_mode);
    FileMode get_mode() const;

private:
    //!< \cond DOXY_IMPL
    std::string m_id;
    std::string m_path;
    uint64_t m_size = 0;
    // uint32_t flags;
    FileMode m_mode = FileMode::NOT_SET;
    // uint16_t id_abbrev;
    //!< \endcond
};

} // namespace esys::repo::git
