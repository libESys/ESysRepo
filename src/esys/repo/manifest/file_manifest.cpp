/*!
 * \file esys/repo/manifest/file_manifest.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/manifest/file.h"
#include "esys/repo/manifest/xmlfile.h"

#include <fstream>

namespace esys::repo::manifest
{

File::File() = default;

File::~File() = default;

int File::read(const std::string &path)
{
    std::ifstream ifs;

    ifs.open(path);
    if (!ifs.is_open()) return -1;

    std::string line;
    std::getline(ifs, line);
    ifs.close();

    if (line.find("<?xml") != std::string::npos)
    {
        manifest::XMLFile xml_file;

        xml_file.set_data(get_data());
        int result = xml_file.read(path);
        if (result < 0) return result;

        xml_file.get_data()->set_format(manifest::Format::XML);
        set_data(xml_file.get_data());
        return 0;
    }
    else
    {
        //! \TODO implement manifest with JSON format ... if ever ...
        return -1;
    }
}

int File::write(const std::string &path)
{
    std::ofstream ofs(path);

    if (!ofs.is_open()) return -1;

    return write(ofs);
}

int File::write(std::ostream &os)
{
    if (get_data() == nullptr) return -1;
    if (get_data()->get_format() == manifest::Format::NOT_SET) return -2;
    if (get_data()->get_format() == manifest::Format::UNKNOWN) return -3;

    if (get_data()->get_format() == manifest::Format::XML)
    {
        manifest::XMLFile xml_file;

        xml_file.set_data(get_data());

        return xml_file.write(os);
    }

    if (get_data()->get_format() == manifest::Format::JSON)
    {
        //! \TODO
        return -4;
    }
    return -5;
}

FileBase *File::get_impl()
{
    return m_impl.get();
}

const FileBase *File::get_impl() const
{
    return m_impl.get();
}

} // namespace esys::repo::manifest
