/*!
 * \file esys/repo/configfileimpl.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/configfileimpl.h"

#include <boost/filesystem.hpp>

#include <fstream>
#include <iomanip>

namespace esys
{

namespace repo
{

ConfigFileImpl::ConfigFileImpl(ConfigFile *self)
    : m_self(self)
{
}

ConfigFileImpl::~ConfigFileImpl()
{
}

int ConfigFileImpl::open(const std::string &path)
{
    if (self()->get_config() == nullptr) self()->set_config(std::make_shared<Config>());

    std::ifstream fin(path);
    json obj;

    if (!fin.is_open()) return -1;

    try
    {
        fin >> obj;
    }
    catch (json::parse_error &err)
    {
        return -1;
    }

    if (!obj.contains("manifest_type")) return -1;

    manifest::Type type;
    int result = manifest::convert(obj["manifest_type"], type);
    if (result < 0) return result;

    self()->get_config()->set_manifest_type(type);

    if (obj.contains("manifest_path"))
    {
        self()->get_config()->set_manifest_path(obj["manifest_path"]);
    }

    if (obj.contains("manifest_kind"))
    {
        manifest::Kind kind;

        result = convert(obj["manifest_kind"], kind);
        if (result < 0) return result;

        self()->get_config()->set_manifest_kind(kind);
    }

    if (obj.contains("manifest_format"))
    {
        manifest::Format format;

        result = convert(obj["manifest_format"], format);
        if (result < 0) return result;

        self()->get_config()->set_manifest_format(format);
    }
    return 0;
}

int ConfigFileImpl::write(const std::string &path)
{
    if (self()->get_config() == nullptr) return -1;

    auto cfg = self()->get_config();

    if (cfg == nullptr) return -1;

    json cfg_json;
    std::string text;
    int result = manifest::convert(cfg->get_manifest_type(), text);
    if (result < 0) return result;

    cfg_json["manifest_type"] = text;
    if (!cfg->get_manifest_path().empty()) cfg_json["manifest_path"] = cfg->get_manifest_path();

    std::string kind;
    result = convert(cfg->get_manifest_kind(), kind);
    if (result < 0) return result;
    cfg_json["manifest_kind"] = kind;

    std::string format;
    result = convert(cfg->get_manifest_format(), format);
    if (result < 0) return result;
    cfg_json["manifest_format"] = format;

    std::ofstream ofs;

    if (boost::filesystem::exists(path))
        ofs.open(path.c_str(), std::ios_base::trunc);
    else
        ofs.open(path.c_str(), std::ios_base::out);

    if (!ofs.is_open()) return -1;

    ofs << std::setw(4);

    ofs << cfg_json;

    ofs.close();

    return 0;
}

ConfigFile *ConfigFileImpl::self()
{
    return m_self;
}

const ConfigFile *ConfigFileImpl::self() const
{
    return m_self;
}

} // namespace repo

} // namespace esys
