// PySwig 0.1.0

/*!
 * \file esys/repo/manifest/fileerror.h
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

#pragma once

#include "esys/repo/esysrepo_defs.h"

#include <string>

//<swig_inc>
%{
#include "esys/repo/manifest/fileerror.h"
%}
//</swig_inc>

namespace esys::repo::manifest
{

/*! \class FileBase esys/repo/manifest/fileerror.h "esys/repo/manifest/fileerror.h"
 * \brief
 */
class ESYSREPO_API FileError
{
public:
    //! Default constructor
    FileError();

    //! Destructor
    ~FileError();

    //! Set the error message
    /*!
     * \param[in] msg the error message
     */
    void set_msg(const std::string &msg);

    //! Get the error message
    /*!
     * \return the error message
     */
    const std::string &get_msg();

    //! Set the error value
    /*!
     * \param[in] value the error value
     */
    void set_value(int value);

    //! Get the error value
    /*!
     * \return the error value
     */
    int get_value() const;

    //! Set the line number where the error occured
    /*!
     * \param[in] line_number where the error occured
     */
    void set_line_number(int line_number);

    //! Get the line number where the error occured
    /*!
     * \return the error value
     */
    int get_line_number() const;

private:
    //!< \cond DOXY_IMPL
    int m_value = 0;        //!< The error value
    std::string m_msg;      //!< The error message
    int m_line_number = -1; //!< The line number where the error occured
    //!< \endcond
};

} // namespace esys::repo::manifest
