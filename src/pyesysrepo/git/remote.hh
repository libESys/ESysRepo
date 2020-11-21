// PySwig 0.0.1

/*!
 * \file esys/repo/git/remote.h
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

//<swig_inc>
%{
#include "esys/repo/git/remote.h"
%}
//</swig_inc>

namespace esys
{

namespace repo
{

namespace git
{

/*! \class Remote esys/repo/git/remote.h "esys/repo/git/remote.h"
 * \brief Hold information about a git branch
 */
class ESYSREPO_API Remote
{
public:
    //! Default constructor
    Remote();

    //! Destructor
    virtual ~Remote();

    //! Set the name of the remote
    /*!
     * \param[in] name the name of the remote
     */
    void set_name(const std::string &name);

    //! Get the name of the remote
    /*!
     * \return the name of the remote
     */
    const std::string &get_name() const;

    //! Set the url of the remote
    /*!
     * \param[in] url the url of the remote
     */
    void set_url(const std::string &url);

    //! Get the url of the remote
    /*!
     * \return the url of the remote
     */
    const std::string &get_url() const;

protected:
    //!< \cond DOXY_IMPL
    std::string m_name; //!< The name of the remote
    std::string m_url;  //!< The url of the remote
    //!< \endcond
};

} // namespace git

} // namespace repo

} // namespace esys
