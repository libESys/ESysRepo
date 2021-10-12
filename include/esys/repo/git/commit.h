/*!
 * \file esys/repo/git/commit.h
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

#include <string>

//<swig_inc/>

namespace esys
{

namespace repo
{

namespace git
{

/*! \class Commit esys/repo/git/commit.h "esys/repo/git/commit.h"
 * \brief Hold information about a commit
 */
class ESYSREPO_API Commit
{
public:
    //! Default constructor
    Commit();

    //! Destructor
    virtual ~Commit();

    //! Set the commit hash
    /*!
     * \param[in] hash the commit hash
     */
    void set_hash(const std::string &hash);

    //! Get the commit hash
    /*!
     * \return the commit hash
     */
    const std::string &get_hash() const;

private:
    //!< \cond DOXY_IMPL
    std::string m_hash;
    //!< \endcond
};

} // namespace git

} // namespace repo

} // namespace esys
