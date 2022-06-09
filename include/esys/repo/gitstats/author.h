/*!
 * \file esys/repo/gitstats/author.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2022 Michel Gillet
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

namespace esys::repo::gitstats
{

/*! \class Author esys/repo/gitstats/author.h "esys/repo/gitstats/author.h"
 * \brief Hold information about an author
 */
class ESYSREPO_API Author
{
public:
    //! Default constructor
    Author();

    //! Destructor
    ~Author();

    //! Set the name of the author
    /*!
     * \param[in] name the name of the author
     */
    void set_name(const std::string &name);

    //! Get the name of the author
    /*!
     * \return the name of the author
     */
    const std::string &get_name() const;

    //! Set the email of the author
    /*!
     * \param[in] email the email of the author
     */
    void set_email(const std::string &email);

    //! Get the email of the author
    /*!
     * \return the email of the author
     */
    const std::string &get_email() const;

private:
    //!< \cond DOXY_IMPL
    std::string m_name;  //!< The name of the author
    std::string m_email; //!< The email of the author

    //!< \endcond
};

} // namespace esys::repo::gitstats
