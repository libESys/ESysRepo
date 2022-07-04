/*!
 * \file esys/repo/git/commit.h
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
#include "esys/repo/git/commithash.h"

#include <string>
#include <chrono>

//<swig_inc/>

namespace esys::repo::git
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
    const CommitHash &get_hash() const; //<swig_out/>

    //! Get the commit hash
    /*!
     * \return the commit hash
     */
    CommitHash &get_hash();

    void set_message(const std::string &message);
    const std::string &get_message() const;

    void set_author(const std::string &author);
    const std::string &get_author() const;

    void set_email(const std::string &email);
    const std::string &get_email() const;

    void set_date_time(const std::chrono::system_clock::time_point &date_time);
    const std::chrono::system_clock::time_point &get_date_time() const;

private:
    //!< \cond DOXY_IMPL
    CommitHash m_hash;
    std::string m_message;
    std::string m_author;
    std::string m_email;
    std::chrono::system_clock::time_point m_date_time;
    //!< \endcond
};

} // namespace esys::repo::git
