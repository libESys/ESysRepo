/*!
 * \file esys/repo/git/branches.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2021 Michel Gillet
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
#include "esys/repo/git/branch.h"

#include <memory>
#include <vector>

//<swig_inc/>

namespace esys
{

namespace repo
{

namespace git
{

/*! \class Branch esys/repo/git/branches.h "esys/repo/git/branches.h"
 * \brief Hold information about all branches of a git repo
 */
class ESYSREPO_API Branches
{
public:
    //! Default constructor
    Branches();

    //! Constructor
    explicit Branches(const std::vector<Branch> &branches);

    //! Destructor
    virtual ~Branches();

    //! Add a branch
    /*!
     * \param[in] branch the branch to add
     */
    void add(std::shared_ptr<Branch> branch);

    //! Clear all branches
    /*!
     */
    void clear();

    //! Get the head
    /*!
     * \param[in] is_head true if this branch is the head/default branch
     */
    std::shared_ptr<Branch> get_head();

    std::size_t size() const;

    //! Sort the branches such that the head is the first one
    /*!
     */
    void sort();

    std::vector<std::shared_ptr<Branch>> &get();
    const std::vector<std::shared_ptr<Branch>> &get() const;

    std::shared_ptr<Branch> find(const std::string &name);

private:
    //!< \cond DOXY_IMPL
    std::vector<std::shared_ptr<Branch>> m_branches; //!< All the branches
    std::shared_ptr<Branch> m_head;
    //!< \endcond
};

} // namespace git

} // namespace repo

} // namespace esys
