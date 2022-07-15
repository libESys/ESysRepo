/*!
 * \file esys/repo/manifest/location_manifest.cpp
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
#include "esys/repo/manifest/location.h"
#include "esys/repo/manifest/repository.h"

#include <Poco/URI.h>

#include <boost/filesystem.hpp>

namespace esys::repo::manifest
{

Location::Location()
    : std::enable_shared_from_this<Location>()
{
}

Location::Location(const std::string &name, const std::string &address)
    : std::enable_shared_from_this<Location>()
    , m_name(name)
    , m_address(address)
{
}

Location::~Location() = default;

void Location::set_name(const std::string &name)
{
    m_name = name;
}

const std::string &Location::get_name() const
{
    return m_name;
}

void Location::set_address(const std::string &address)
{
    m_address = address;
}

const std::string &Location::get_address() const
{
    return m_address;
}

bool Location::is_address_ssh() const
{
    return get_address().find("ssh://") != get_address().npos;
}

void Location::set_alt_address(const std::string &alt_address)
{
    m_alt_address = alt_address;
}

const std::string &Location::get_alt_address() const
{
    return m_alt_address;
}

bool Location::is_alt_address_ssh() const
{
    return get_alt_address().find("ssh://") != get_alt_address().npos;
}

std::shared_ptr<Repository> Location::add_repo(const std::string &name, const std::string &path)
{
    auto repo = std::make_shared<Repository>(name, path);

    add_repo(repo);
    return repo;
}

void Location::add_repo(std::shared_ptr<Repository> repo)
{
    repo->set_location(this);

    get_repos().push_back(repo);
    m_map_repos_by_name[repo->get_name()] = repo;
    m_map_repos_by_path[repo->get_path()] = repo;
}

std::vector<std::shared_ptr<Repository>> &Location::get_repos()
{
    return m_repos;
}

const std::vector<std::shared_ptr<Repository>> &Location::get_repos() const
{
    return m_repos;
}

std::shared_ptr<Repository> Location::find_repo_by_path(const std::string &path)
{
    boost::filesystem::path gen_path = path;

    auto it = m_map_repos_by_path.find(gen_path.generic().string());

    if (it == m_map_repos_by_path.end()) return nullptr;
    return it->second;
}

std::shared_ptr<Repository> Location::find_repo_by_name(const std::string &name)
{
    auto it = m_map_repos_by_name.find(name);

    if (it == m_map_repos_by_name.end()) return nullptr;
    return it->second;
}

std::string Location::find_repo_path_by_url(const std::string &url)
{
    auto repo = find_repo_by_url(url);

    if (repo == nullptr) return "";
    return repo->get_path();
}

std::shared_ptr<manifest::Repository> Location::find_repo_by_url(const std::string &url)
{
    std::string url_ = url;
    remove_dot_git(url_);
    Poco::URI uri_repo(url_);

    std::string auth = uri_repo.getAuthority(); // "www.appinf.com:88"
    std::string host = uri_repo.getHost();      // "www.appinf.com"
    unsigned short port = uri_repo.getPort();   // 88
    std::string path = uri_repo.getPath();      // "/sample"

    for (auto repo : get_repos())
    {
        std::string uri_txt = get_address();
        if (repo->get_name()[0] != '/') uri_txt += "/";
        uri_txt += repo->get_name();
        remove_dot_git(uri_txt);
        Poco::URI this_uri_repo(uri_txt);
        if ((auth == this_uri_repo.getAuthority()) && (path == this_uri_repo.getPath())) return repo;
        if ((host == this_uri_repo.getHost()) && (path == this_uri_repo.getPath())) return repo;
    }

    return nullptr;
}

void Location::remove_dot_git(std::string &text)
{
    auto idx = text.rfind(".git");
    if (idx == text.npos) return;

    text = text.substr(0, idx);
}

bool Location::operator==(const Location &location) const
{
    if (get_name() != location.get_name()) return false;
    if (get_address() != location.get_address()) return false;

    if (get_repos().size() != location.get_repos().size()) return false;

    for (std::size_t idx = 0; idx < get_repos().size(); ++idx)
    {
        if (*get_repos()[idx] != *location.get_repos()[idx]) return false;
    }
    return true;
}

bool Location::operator!=(const Location &location) const
{
    return !operator==(location);
}

ESYSREPO_API std::ostream &operator<<(std::ostream &os, const Location &location)
{
    return os;
}

} // namespace esys::repo::manifest
