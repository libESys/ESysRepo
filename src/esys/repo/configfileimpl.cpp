/*!
 * \file esys/repo/configfileimpl.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/configfileimpl.h"

#include <boost/filesystem.hpp>

#include <fstream>
#include <iomanip>

namespace esys::repo
{

ConfigFileImpl::ConfigFileImpl(ConfigFile *self)
    : m_self(self)
{
}

ConfigFileImpl::~ConfigFileImpl() = default;

Result ConfigFileImpl::open(const std::string &path)
{
    if (self()->get_config() == nullptr) self()->set_config(std::make_shared<Config>());

    std::ifstream fin(path);
    json obj;

    if (!fin.is_open()) return ESYSREPO_RESULT(ResultCode::ERROR_OPENING_FILE, path);

    try
    {
        fin >> obj;
    }
    catch (json::parse_error &err)
    {
        return ESYSREPO_RESULT(ResultCode::CFGFILE_ERROR_PARSING_FILE, path);
    }

    if (!obj.contains("manifest_type")) return ESYSREPO_RESULT(ResultCode::CFGFILE_NO_MANIFEST_TYPE, path);

    manifest::Type type = manifest::Type::NOT_SET;

    std::string value = obj["manifest_type"];
    Result result = manifest::convert(value, type);
    if (result.error()) return ESYSREPO_RESULT(result, ResultCode::CFGFILE_UNKNOWN_MANIFEST_TYPE, value);

    self()->get_config()->set_manifest_type(type);

    if (!obj.contains("manifest_url")) return ESYSREPO_RESULT(ResultCode::CFGFILE_NO_MANIFEST_URL, path);
    self()->get_config()->set_manifest_url(obj["manifest_url"]);

    if (obj.contains("manifest_path"))
    {
        self()->get_config()->set_manifest_path(obj["manifest_path"]);
    }

    if (obj.contains("manifest_kind"))
    {
        manifest::Kind kind;

        std::string value = obj["manifest_kind"];
        auto result = convert(value, kind);
        if (result.error()) return ESYSREPO_RESULT(result, ResultCode::CFGFILE_UNKNOWN_MANIFEST_KIND, value);

        self()->get_config()->set_manifest_kind(kind);
    }

    if (obj.contains("manifest_format"))
    {
        manifest::Format format;

        std::string value = obj["manifest_format"];
        auto result = convert(value, format);
        if (result.error()) return ESYSREPO_RESULT(result, ResultCode::CFGFILE_UNKNOWN_MANIFEST_FORMAT, value);

        self()->get_config()->set_manifest_format(format);
    }
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result ConfigFileImpl::write(const std::string &path)
{
    if (self()->get_config() == nullptr) return ESYSREPO_RESULT(ResultCode::INTERNAL_ERROR);

    auto cfg = self()->get_config();

    if (cfg == nullptr) return ESYSREPO_RESULT(ResultCode::INTERNAL_ERROR);

    json cfg_json;
    std::string text;
    Result result = manifest::convert(cfg->get_manifest_type(), text);
    if (result.error()) return ESYSREPO_RESULT(result);

    cfg_json["manifest_type"] = text;
    if (!cfg->get_manifest_path().empty()) cfg_json["manifest_path"] = cfg->get_manifest_path();
    if (!cfg->get_manifest_url().empty()) cfg_json["manifest_url"] = cfg->get_manifest_url();

    std::string kind;
    result = convert(cfg->get_manifest_kind(), kind);
    if (result.error()) return ESYSREPO_RESULT(result);
    cfg_json["manifest_kind"] = kind;

    std::string format;
    result = convert(cfg->get_manifest_format(), format);
    if (result.error()) return ESYSREPO_RESULT(result);
    cfg_json["manifest_format"] = format;

    std::ofstream ofs;

    if (boost::filesystem::exists(path))
        ofs.open(path.c_str(), std::ios_base::trunc);
    else
        ofs.open(path.c_str(), std::ios_base::out);

    if (!ofs.is_open()) return ESYSREPO_RESULT(ResultCode::ERROR_OPENING_FILE, path);

    ofs << std::setw(4);

    ofs << cfg_json;

    ofs.close();

    return ESYSREPO_RESULT(ResultCode::OK);
}

ConfigFile *ConfigFileImpl::self()
{
    return m_self;
}

const ConfigFile *ConfigFileImpl::self() const
{
    return m_self;
}

} // namespace esys::repo
