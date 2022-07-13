/*!
 * \file esys/repo/manifest/include.h
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

//<swig>%shared_ptr(esys::repo::manifest::Include);</swig>

namespace esys::repo::manifest
{

/*! \class Group esys/repo/manifest/include.h "esys/repo/manifest/include.h"
 * \brief Data for an include from a manifest
 */
class ESYSREPO_API Include
{
public:
    //! Default constructor
    Include();

    //! Constructor
    explicit Include(const std::string &name);

    //! Destructor
    ~Include();

    //! Set the name of the location
    /*!
     * \param[in] name the name of the location
     */
    void set_name(const std::string &name);

    //! Get the name of the location
    /*!
     * \return the name of the location
     */
    const std::string &get_name() const;

    //! Equal to comparison operator
    bool operator==(const Include &other) const;

    //! Not equal to comparison operator
    bool operator!=(const Include &other) const;

private:
    //!< \cond DOXY_IMPL
    std::string m_name; //!< The name of this include

    //!< \endcond
};

} // namespace esys::repo::manifest
