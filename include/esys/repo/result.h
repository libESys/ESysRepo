/*!
 * \file esys/repo/result.h
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
#include "esys/repo/errorinfo.h"

#include <memory>
#include <ostream>

#ifdef __has_include
#if __has_include(<version>)
#ifdef __cpp_lib_source_location
#include <source_location>
#endif
#endif
#endif

#ifdef _MSC_VER
#define ESYSREPO_RESULT(result, ...) esys::repo::Result(result, __FILE__, __LINE__, __FUNCSIG__, __VA_ARGS__)
#else
#define ESYSREPO_RESULT(result, ...) esys::repo::Result(result, __FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__)
#endif

//<swig_inc/>

namespace esys::repo
{

/*! \class Result esys/repo/result.h "esys/repo/result.h"
 * \brief
 */
class ESYSREPO_API Result
{
public:
    //! Default constructor
    Result();

    //! Copy constructor
    Result(const Result &result);

    //! Constructor
    /*!
     * \param[in] result_code the result code
     * \param[in] file the file where the Result was created
     * \param[in] line_number the line number when the Result was created
     * \param[in] function the name of the function where the Result was created
     */
    Result(ResultCode result_code, const std::string &file = "", int line_number = -1,
           const std::string &function = "");

    //! Constructor
    /*!
     * \param[in] result_code the result code
     * \param[in] file the file where the Result was created
     * \param[in] line_number the line number when the Result was created
     * \param[in] function the name of the function where the Result was created
     * \param[in] text some informative text in case of error
     */
    Result(ResultCode result_code, const std::string &file, int line_number, const std::string &function,
           const std::string &text);

    //! Constructor
    /*!
     * \param[in] result_code the result code
     * \param[in] file the file where the Result was created
     * \param[in] line_number the line number when the Result was created
     * \param[in] function the name of the function where the Result was created
     * \param[in] raw_error error from an external library
     * \param[in] text some informative text in case of error
     */
    Result(ResultCode result_code, const std::string &file, int line_number, const std::string &function, int raw_error,
           const std::string &text = "");

    //! Constructor
    /*!
     * \param[in] result the parent Result
     * \param[in] file the file where the Result was created
     * \param[in] line_number the line number when the Result was created
     * \param[in] function the name of the function where the Result was created
     */
    Result(const Result &result, const std::string &file, int line_number, const std::string &function);

    //! Constructor
    /*!
     * \param[in] result the parent Result
     * \param[in] file the file where the Result was created
     * \param[in] line_number the line number when the Result was created
     * \param[in] function the name of the function where the Result was created
     * \param[in] text some informative text in case of error
     */
    Result(const Result &result, const std::string &file, int line_number, const std::string &function,
           const std::string &text);

    //! Destructor
    ~Result();

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

    //! Get the result code as an integer
    /*!
     * \return the result code
     */
    int get_result_code_int() const;

    //! Set the error information
    /*!
     * \param[in] error_info the error information
     */
    void set_error_info(std::shared_ptr<ErrorInfo> error_info);

    //! Get the error information
    /*!
     * \return the error information
     */
    std::shared_ptr<ErrorInfo> get_error_info();

    //! Get the error information
    /*!
     * \return the error information
     */
    const std::shared_ptr<ErrorInfo> get_error_info() const; //<swig_out/>

    //! Returns if the Result is successful, meaning no error occured
    /*!
     * \return true if not errors, false otherwise
     */
    bool success() const;

    //! Returns if the Result is successful, meaning no error occured
    /*!
     * \return true if not errors, false otherwise
     */
    bool ok() const;

    //! Returns if the Result is failed, meaning an error occured
    /*!
     * \return true if there was an error, false otherwise
     */
    bool error() const;

    //! Conversion operator to ResultCode
    /*!
     * \return the result ode
     */
    operator ResultCode() const; //<swig_out/>

    //! Assignment operator
    /*!
     * \return the result code
     */
    Result &operator=(const Result &other); //<swig_out/>

    //! Equal comparison operator
    bool operator==(const ResultCode &result_code);

    //! Not equal comparison operator
    bool operator!=(const ResultCode &result_code);

private:
    //!< \cond DOXY_IMPL
    ResultCode m_result_code = ResultCode::OK; //!< The result code
    std::shared_ptr<ErrorInfo> m_error_info;   //!< The error information
    //!< \endcond
};

ESYSREPO_API bool operator==(const Result &result, const ResultCode &result_code);
ESYSREPO_API bool operator!=(const Result &result, const ResultCode &result_code);

ESYSREPO_API bool operator==(const ResultCode &result_code, const Result &result);
ESYSREPO_API bool operator!=(const ResultCode &result_code, const Result &result);

} // namespace esys::repo

namespace std
{

ESYSREPO_API ostream &operator<<(ostream &os, const esys::repo::Result &result); //<swig_out/>
}
