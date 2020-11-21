/*!
 * \file esys/repo/git/diffdelta.h
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
#include "esys/repo/git/diffdeltatype.h"
#include "esys/repo/git/difffile.h"

#include <string>
#include <memory>
#include <vector>

//<swig_inc/>

namespace esys
{

namespace repo
{

namespace git
{

/*! \class DiffDelta esys/repo/git/diffdelta.h "esys/repo/git/diffdelta.h"
 * \brief
 */
class ESYSREPO_API DiffDelta
{
public:
    //! Default constructor
    DiffDelta();

    //! Destructor
    virtual ~DiffDelta();

    void set_type(DiffDeltaType type);
    DiffDeltaType get_type() const;

    void set_similatiry(std::size_t similarity);
    std::size_t get_similarity() const;

    void set_file_count(std::size_t file_count);
    std::size_t get_file_count() const;
    
    DiffFile &get_old_file();
    const DiffFile &get_old_file() const;
    
    DiffFile &get_new_file();
    const DiffFile &get_new_file() const;

protected:
    //!< \cond DOXY_IMPL
    DiffDeltaType m_type = DiffDeltaType::NOT_SET;

    // uint32_t flags;      /**< git_diff_flag_t values */
    std::size_t m_similarity;     //!< for RENAMED and COPIED, value 0-100
    std::size_t m_file_count = 0; //!< the number of files in this delta
    DiffFile m_old_file;
    DiffFile m_new_file;
    //!< \endcond
};

} // namespace git

} // namespace repo

} // namespace esys
