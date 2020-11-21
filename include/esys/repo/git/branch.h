/*!
 * \file esys/repo/git/branch.h
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
#include "esys/repo/git/branchtype.h"

#include <string>

//<swig_inc/>

namespace esys
{

namespace repo
{

namespace git
{

/*! \class Branch esys/repo/git/branch.h "esys/repo/git/branch.h"
 * \brief Hold information about a git branch
 */
class ESYSREPO_API Branch
{
public:
    //! Default constructor
    Branch();

    //! Constructor
    /*!
     * \param[in] name the name of the branch
     * \param[in] is_head true if this is current branch, false otherwise
    */
    Branch(const std::string &name, bool is_head);

    //! Constructor
    //! Constructor
    /*!
     * \param[in] name the name of the branch
     * \param[in] type the type of the branch, e.g. local or remote
     * \param[in] is_head true if this is current branch, false otherwise
     */
    Branch(const std::string &name, BranchType type, bool is_head);

    //! Destructor
    virtual ~Branch();

    //! Set the name of the branch
    /*!
     * \param[in] name the name of the branch
     */
    void set_name(const std::string &name);

    //! Get the name of the branch
    /*!
     * \return the name of the branch
     */
    const std::string &get_name() const;

    //! Set the type of the branch
    /*!
     * \param[in] type the type of the branch
     */
    void set_type(BranchType type);

    //! Get the type of the branch
    /*!
     * \return the type of the branch
     */
    BranchType get_type() const;

    //! Set if the branch is the default branch
    /*!
     * \param[in] is_head true if this branch is the head/default branch
     */
    void set_is_head(bool is_head);

    //! Get if the branch is the default branch
    /*!
     * \return true if this branch is the head/default branch
     */
    bool get_is_head() const;

protected:
    //!< \cond DOXY_IMPL
    std::string m_name;                      //!< The name of the branch
    BranchType m_type = BranchType::NOT_SET; //!< The type of branch
    bool m_is_head = false;                  //!< True if default branch
    //!< \endcond
};

} // namespace git

} // namespace repo

} // namespace esys
