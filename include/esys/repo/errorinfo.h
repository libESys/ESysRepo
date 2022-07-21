/*!
 * \file esys/repo/errorinfo.h
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
#include "esys/repo/resultcode.h"

#include <memory>
#include <ostream>
#include <string>

//<swig_inc/>

//<swig>%shared_ptr(esys::repo::ErrorInfo);</swig>

namespace esys::repo
{

/*! \class ErrorInfo esys/repo/errorinfo.h "esys/repo/errorinfo.h"
 * \brief
 */
class ESYSREPO_API ErrorInfo
{
public:
    //! Default constructor
    ErrorInfo();

    //! Destructor
    virtual ~ErrorInfo();

    //! Set the index in the error call stack
    /*!
     * \param[in] index the index in the error call stack
     */
    void set_index(int index);

    //! Get the index in the error call stack
    /*!
     * \return the index in the error call stack
     */
    int get_index() const;

    //! Set the result code
    /*!
     * \param[in] result_code the result code
     */
    void set_result_code(ResultCode result_code);

    //! Get the result code
    /*!
     * \return the result code
     */
    ResultCode get_result_code() const;

    //! Set the file path where the error occured
    /*!
     * \param[in] file the file path where the error occured
     */
    void set_file(const std::string &file);

    //! Get the file path where the error occured
    /*!
     * \return the file path where the error occured
     */
    const std::string &get_file() const;

    //! Set the line number where the error occured
    /*!
     * \param[in] line_number the line number where the error occured
     */
    void set_line_number(int line_number);

    //! Get the line number where the error occured
    /*!
     * \return the line number where the error occured
     */
    int get_line_number() const;

    //! Set the function where the error occured
    /*!
     * \param[in] function the function where the error occured
     */
    void set_function(const std::string &function);

    //! Get the function where the error occured
    /*!
     * \return the function where the error occured
     */
    const std::string &get_function() const;

    //! Set the previous error information
    /*!
     * \param[in] prev the previous error information
     */
    void set_prev(std::shared_ptr<ErrorInfo> prev);

    //! Get the previous error information
    /*!
     * \return the previous error information
     */
    std::shared_ptr<ErrorInfo> get_prev();

private:
    //!< \cond DOXY_IMPL
    int m_index = 0;                                //!< The index in the error call stack
    ResultCode m_result_code = ResultCode::SUCCESS; //!< The result code
    std::string m_file;                             //!< The file path where the error occured
    int m_line_number = -1;                         //!< The line number where the error occured
    std::string m_function;                         //!< The function where the error occured
    std::shared_ptr<ErrorInfo> m_prev;              //!< The previous error information
    //!< \endcond
};

} // namespace esys::repo

namespace std
{

ESYSREPO_API ostream &operator<<(ostream &os, const esys::repo::ErrorInfo &error_info);

}
