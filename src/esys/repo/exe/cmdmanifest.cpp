/*!
 * \file esys/repo/exe/cmdmanifest.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/exe/cmdmanifest.h"
#include "esys/repo/manifest/file.h"
#include "esys/repo/grepo/manifest.h"
#include "esys/repo/manifest/xmlfile.h"
#include "esys/repo/manifest/repository.h"
#include "esys/repo/githelper.h"

#include <boost/filesystem.hpp>

#include <iostream>
#include <fstream>

namespace esys::repo::exe
{

CmdManifest::CmdManifest()
    : Cmd("Manifest")
{
}

CmdManifest::~CmdManifest() = default;

void CmdManifest::set_revision_as_head(bool revision_as_head)
{
    m_revision_as_head = revision_as_head;
}

bool CmdManifest::get_revision_as_head() const
{
    return m_revision_as_head;
}

void CmdManifest::set_output_file(const std::string &output_file)
{
    m_output_file = output_file;
}

const std::string &CmdManifest::get_output_file() const
{
    return m_output_file;
}

Result CmdManifest::update_revision_as_head()
{
    for (auto location : get_manifest()->get_locations())
    {
        for (auto repo : location->get_repos())
        {
            Result result = update_revision_as_head(repo);
            if (result.error()) return ESYSREPO_RESULT(result);
        }
    }
    return ESYSREPO_RESULT(ResultCode::OK);
}

Result CmdManifest::update_revision_as_head(std::shared_ptr<manifest::Repository> repo)
{
    auto git_helper = new_git_helper();

    boost::filesystem::path repo_path = get_config_folder()->get_workspace_path();
    repo_path /= repo->get_path();
    repo_path = boost::filesystem::absolute(repo_path).normalize().make_preferred();

    std::string revision = repo->get_revision();
    if (revision.empty()) revision = get_manifest()->get_default_revision();

    Result rresult = git_helper->open(repo_path.string(), log::Level::DEBUG);
    if (rresult.error()) return ESYSREPO_RESULT(rresult);

    rresult = git_helper->fetch(log::Level::DEBUG);
    if (rresult.error()) return ESYSREPO_RESULT(rresult);

    std::string hash;
    int result_int = git_helper->get_hash(revision, hash, log::Level::DEBUG);
    if (result_int < 0)
    {
        git_helper->close(log::Level::DEBUG);
        return generic_error(result_int);
    }
    repo->set_revision(hash);

    return git_helper->close(log::Level::DEBUG);
}

Result CmdManifest::impl_run()
{
    Result rresult = only_one_folder_or_workspace();
    if (rresult.error()) return ESYSREPO_RESULT(rresult);

    int result = open_esysrepo_folder();
    if (result < 0) return generic_error(result);

    result = load_manifest();
    if (result < 0) return generic_error(result);

    if (get_revision_as_head())
    {
        rresult = update_revision_as_head();
        if (rresult.error())
        {
            std::string err_str = "Failed to get the revision as HEAD";
            error(err_str);
            return ESYSREPO_RESULT(rresult, err_str);
        }
    }

    std::shared_ptr<std::ofstream> fos;
    std::ostream *os = nullptr;

    if (get_output_file().empty())
        os = &std::cout;
    else
    {
        fos = std::make_shared<std::ofstream>(get_output_file());
        os = fos.get();
    }

    std::shared_ptr<manifest::FileBase> file;

    switch (get_manifest()->get_type())
    {
        case manifest::Type::GOOGLE_MANIFEST: file = std::make_shared<grepo::Manifest>(); break;
        case manifest::Type::ESYSREPO_MANIFEST: file = std::make_shared<manifest::XMLFile>(); break;
        default: error("Manifest format not supported."); return generic_error(-1);
    }

    file->set_data(get_manifest());
    result = file->write(*os);

    if (fos != nullptr) fos->close();
    return generic_error(result);
}

} // namespace esys::repo::exe
