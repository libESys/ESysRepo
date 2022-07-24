/*!
 * \file esys/repo/errorstack.h
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
#include "esys/repo/result.h"

#include <memory>
#include <vector>

//<swig_inc/>

namespace esys::repo
{

/*! \class ErrorStack esys/repo/errorstack.h "esys/repo/errorstack.h"
 * \brief Create human readable output from the Result of a function call
 */
class ESYSREPO_API ErrorStack
{
public:
    //! Default constructor
    ErrorStack();

    //! Constructor
    /*!
     * \param[in] result the Result to create the output from
     */
    ErrorStack(const Result &result);

    //! Destructor
    virtual ~ErrorStack();

    //! Analyze and generate the human readable output
    /*!
     * \param[in] result  the Result to create the output from
     * \return 0 if successful, < 0 otherwise
     */
    int analyze(const Result &result);

    //! Analyze and generate the human readable output
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    int analyze();

    //! Get the generated human readable output
    /*!
     * \return the generated human readable output
     */
    const std::string &get_output() const;

    //! Set the Result to create the output from
    /*!
     * \param[in] result the Result to create the output from
     */
    void set_result(const Result &result);

    //! Get the Result to create the output from
    /*!
     * \return the Result to create the output from
     */
    const Result &get_result() const;

    //! Get the stack of errors
    /*!
     * \return the stack of errors
     */
    const std::vector<std::shared_ptr<ErrorInfo>> &get_error_infos() const;

protected:
    //!< \cond DOXY_IMPL

    //! Generate the human readable output
    /*!
     * \return 0 if successful, < 0 otherwise
     */
    virtual int print();

private:
    Result m_result;                                       //!< The Result of a function call
    std::vector<std::shared_ptr<ErrorInfo>> m_error_infos; //!< The analyzed stack of errors
    std::string m_output;                                  //!< The human readable output
    //!< \endcond
};

} // namespace esys::repo
