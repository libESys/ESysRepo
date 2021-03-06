/*!
 * \file esys/repo/config.h
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
#include "esys/repo/manifest/type.h"
#include "esys/repo/manifest/kind.h"
#include "esys/repo/manifest/format.h"

#include <string>

//<swig_inc/>

//<swig>%shared_ptr(esys::repo::Config);</swig>

namespace esys::repo
{

/*! \class Config esys/repo/config.h "esys/repo/config.h"
 * \brief Hold data of an ESysRepo configuration
 */
class ESYSREPO_API Config
{
public:
    //! Default configuration
    Config();

    //! Destructor
    virtual ~Config();

    //! Set the manifest type
    /*!
     * \param[in] manifest_type the manifest type
     */
    void set_manifest_type(manifest::Type manifest_type);

    //! Get the manifest type
    /*!
     * \return the manifest type
     */
    manifest::Type get_manifest_type() const;

    //! Set the manifest kind
    /*!
     * \param[in] manifest_kind the manifest kind
     */
    void set_manifest_kind(manifest::Kind manifest_kind);

    //! Get the manifest kind
    /*!
     * \return the manifest kind
     */
    manifest::Kind get_manifest_kind() const;

    //! Set the manifest format
    /*!
     * \param[in] manifest_format the manifest format
     */
    void set_manifest_format(manifest::Format manifest_format);

    //! Get the manifest format
    /*!
     * \return the manifest format
     */
    manifest::Format get_manifest_format() const;

    //! Set the manifest path
    /*!
     * \param[in] manifest_path the manifest path
     */
    void set_manifest_path(const std::string &manifest_path);

    //! Get the manifest path
    /*!
     * \return the manifest path
     */
    const std::string &get_manifest_path() const;

    //! Set the manifest url
    /*!
     * \param[in] manifest_url the manifest url
     */
    void set_manifest_url(const std::string &manifest_url);

    //! Get the manifest url
    /*!
     * \return the manifest url
     */
    const std::string &get_manifest_url() const;

    //! Equal to comparison operator
    bool operator==(const Config &cfg) const;

    //! Not equal to comparison operator
    bool operator!=(const Config &cfg) const;

    //! Assignment operator
    Config &operator=(const Config &cfg); //<swig_out/>

    //! Tells if a esysrepo folder exists or not
    /*!
     * \return true if there is a esysrepo folder; otherwise false
     */
    bool has_esysrepo_folder() const;

private:
    //!< \cond DOXY_IMPL
    manifest::Type m_manifest_type = manifest::Type::NOT_SET;       //!< The manifest type
    manifest::Kind m_manifest_kind = manifest::Kind::ISOLATED;      //!< The manifest kind
    manifest::Format m_manifest_format = manifest::Format::NOT_SET; //!< The manifest format
    std::string m_manifest_path;                                    //!< The manifest path
    std::string m_manifest_url;                                     //!< The manifest url
    //!< \endcond
};

} // namespace esys::repo
