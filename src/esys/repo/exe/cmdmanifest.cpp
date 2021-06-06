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

namespace esys
{

namespace repo
{

namespace exe
{

CmdManifest::CmdManifest()
    : Cmd("Manifest")
{
}

CmdManifest::~CmdManifest()
{
}

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

int CmdManifest::update_revision_as_head()
{
    int result = 0;

    for (auto location : get_manifest()->get_locations())
    {
        for (auto repo : location->get_repos())
        {
            result = update_revision_as_head(repo);
            if (result < 0) return -1;
        }
    }
    return 0;
}

int CmdManifest::update_revision_as_head(std::shared_ptr<manifest::Repository> repo)
{
    GitHelper git_helper(get_git(), get_logger_if());

    boost::filesystem::path rel_repo_path;
    boost::filesystem::path repo_path = get_config_folder()->get_workspace_path();
    repo_path /= repo->get_path();
    repo_path = boost::filesystem::absolute(repo_path).normalize().make_preferred();
    rel_repo_path = boost::filesystem::relative(repo_path);

    std::string revision = repo->get_revision();
    if (revision.empty()) revision = get_manifest()->get_default_revision();

    int result = git_helper.open(repo_path.string(), log::Level::DEBUG);
    if (result < 0) return result;

    result = git_helper.fetch(log::Level::DEBUG);
    if (result < 0) return result;

    std::string hash;
    result = git_helper.get_hash(revision, hash, log::Level::DEBUG);
    if (result < 0)
    {
        git_helper.close(log::Level::DEBUG);
        return result;
    }
    repo->set_revision(hash);

    return git_helper.close(log::Level::DEBUG);
}

int CmdManifest::impl_run()
{
    int result = only_one_folder_or_workspace();
    if (result < 0) return result;

    result = open_esysrepo_folder();
    if (result < 0) return result;

    result = load_manifest();
    if (result < 0) return result;

    if (get_revision_as_head())
    {
        result = update_revision_as_head();
        if (result < 0)
        {
            error("Failed to get the revision as HEAD");
            return result;
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

    std::shared_ptr<manifest::File> file;

    switch (get_manifest()->get_type())
    {
        case manifest::Type::GOOGLE_MANIFEST: file = std::make_shared<grepo::Manifest>(); break;
        case manifest::Type::ESYSREPO_MANIFEST: file = std::make_shared<manifest::XMLFile>(); break;
        default: error("Manifest format not supported."); return -1;
    }

    file->set_data(get_manifest());
    result = file->write(*os);

    if (fos != nullptr) fos->close();
    return result;
}

} // namespace exe

} // namespace repo

} // namespace esys
