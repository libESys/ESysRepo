/*!
 * \file esys/repo/manifest/filebase.h
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
#include "esys/repo/manifest.h"
#include "esys/repo/manifest/fileerror.h"
#include "esys/repo/result.h"

#include <string>
#include <memory>

//<swig_inc/>

namespace esys::repo::manifest
{

/*! \class FileBase esys/repo/manifest/filebase.h "esys/repo/manifest/filebase.h"
 * \brief Base class for all ESysRepo manifest file format
 */
class ESYSREPO_API FileBase
{
public:
    //! Default constructor
    FileBase();

    //! Destructor
    virtual ~FileBase();

    //! Set the manifest data
    /*!
     * \param[in] manifest the manifest data
     */
    void set_data(std::shared_ptr<Manifest> manifest);

    //! Get the manifest data
    /*!
     * \return the manifest data
     */
    std::shared_ptr<Manifest> get_data() const;

    //! Read the manifest
    /*!
     * \param[in] path the path of the manifest
     * \return ResultCode::OK if successful, otherwise an error
     */
    virtual Result read(const std::string &path) = 0;

    //! Write this manifest to a file
    /*!
     * \param[in] path the path of the ESysRepo manifest
     * \return 0 if successful, < 0 otherwise
     */
    virtual Result write(const std::string &path) = 0;

    //! Write the manifest to a stream
    /*!
     * \param[in] os the stream
     */
    virtual Result write(std::ostream &os) = 0;

    std::vector<std::shared_ptr<FileError>> &get_errors();
    const std::vector<std::shared_ptr<FileError>> &get_errors() const; //<swig_out/>
    void add_error(std::shared_ptr<FileError> error);
    void add_error(int value, const std::string &msg);
    void add_error(int value, const std::string &msg, int line_number);

    const std::string &get_filename() const;

protected:
    //!< \cond DOXY_IMPL
    void set_filename(const std::string &filename);

private:
    std::string m_filename;
    std::shared_ptr<Manifest> m_data; //!< The abstract data of a manifest
    std::vector<std::shared_ptr<FileError>> m_errors;
    //!< \endcond
};

} // namespace esys::repo::manifest
