/*!
 * \file esys/repo/resultcode.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/resultcode.h"

#include <cassert>

namespace esys::repo
{

int ResultCode::s_cur_id = -1;
std::map<int, std::string> ResultCode::s_map;
std::vector<int> ResultCode::s_ints;

int ResultCode::s_get_cur_id()
{
    return s_cur_id;
}

std::string ResultCode::s_find_name(int id)
{
    auto it = s_map.find(id);
    if (it == s_map.end()) return "";

    return it->second;
}

bool ResultCode::s_is_id(int id)
{
    return s_map.find(id) != s_map.end();
}

const std::vector<int> &ResultCode::s_get_ints()
{
    return s_ints;
}

ResultCode::ResultCode(const std::string &name)
{
    assert(s_is_id(s_cur_id) == false);

    m_id = s_cur_id--;

    s_map[m_id] = name;
    s_ints.push_back(m_id);
}

ResultCode::ResultCode(const std::string &name, int id)
    : m_id(id)
{
    assert(s_is_id(id) == false);

    s_cur_id = id - 1;

    s_map[m_id] = name;
    s_ints.push_back(m_id);
}

ResultCode::~ResultCode() = default;

std::string ResultCode::get_name() const
{
    return s_find_name(get_id());
}

void ResultCode::set_id(int id)
{
    m_id = id;
}

int ResultCode::get_id() const
{
    return m_id;
}

ResultCode::operator int() const
{
    return m_id;
}

ResultCode &ResultCode::operator=(const ResultCode &other)
{
    if (&other == this) return *this;

    m_id = other.get_id();
    return *this;
}

bool ResultCode::operator==(const ResultCode &result_code) const
{
    return m_id == result_code.get_id();
}

bool ResultCode::operator!=(const ResultCode &result_code) const
{
    return m_id != result_code.get_id();
}

DEFINE_RESULT_CODE(OK, 0);
DEFINE_RESULT_CODE(GENERIC_ERROR);
DEFINE_RESULT_CODE(ERROR_OPENING_FILE);
DEFINE_RESULT_CODE(PATH_NOT_EXISTING);
DEFINE_RESULT_CODE(EMPTY_PATH);
DEFINE_RESULT_CODE(FILE_NOT_EXISTING);
DEFINE_RESULT_CODE(INTERNAL_ERROR);
DEFINE_RESULT_CODE(NOT_IMPLEMENTED);
DEFINE_RESULT_CODE(FOLDER_CREATION_ERROR);
DEFINE_RESULT_CODE(FAILED_TO_COPY);
DEFINE_RESULT_CODE(FAILED_TO_REMOVE_ALL);
DEFINE_RESULT_CODE(RAW_INT_ERROR);
DEFINE_RESULT_CODE(FOLDER_ALREADY_EXISTS);

DEFINE_RESULT_CODE(CFGFILE_ERROR_PARSING_FILE, -100);
DEFINE_RESULT_CODE(CFGFILE_NO_MANIFEST_TYPE);
DEFINE_RESULT_CODE(CFGFILE_UNKNOWN_MANIFEST_TYPE);
DEFINE_RESULT_CODE(CFGFILE_NO_MANIFEST_URL);
DEFINE_RESULT_CODE(CFGFILE_UNKNOWN_MANIFEST_KIND);
DEFINE_RESULT_CODE(CFGFILE_UNKNOWN_MANIFEST_FORMAT);

DEFINE_RESULT_CODE(MANIFEST_ERROR_PARSING_FILE, -200);
DEFINE_RESULT_CODE(MANIFEST_NO_LOCATIONS_DEFINED);
DEFINE_RESULT_CODE(MANIFEST_UNKNOWN_ELEMENT);
DEFINE_RESULT_CODE(MANIFEST_UNKNOWN_ATTRIBUTE);
DEFINE_RESULT_CODE(MANIFEST_INCORRECT_ATTRIBUTE_VALUE);
DEFINE_RESULT_CODE(MANIFEST_NO_DEFAULT_LOCATION);
DEFINE_RESULT_CODE(MANIFEST_UNKNOWN_TYPE);
DEFINE_RESULT_CODE(MANIFEST_UNKNOWN_KIND);
DEFINE_RESULT_CODE(MANIFEST_LOCATION_WITHOUT_NAME);
DEFINE_RESULT_CODE(MANIFEST_LOCATION_WITHOUT_ADDRESS);
DEFINE_RESULT_CODE(MANIFEST_REPOSITORY_WITHOUT_NAME);
DEFINE_RESULT_CODE(MANIFEST_REPOSITORY_WITHOUT_PATH);
DEFINE_RESULT_CODE(MANIFEST_GROUP_WITHOUT_NAME);
DEFINE_RESULT_CODE(MANIFEST_GROUP_REPO_WITHOUT_NAME);
DEFINE_RESULT_CODE(MANIFEST_GROUP_REPO_WITHOUT_PATH);
DEFINE_RESULT_CODE(MANIFEST_UNKNOWN_REPO);
DEFINE_RESULT_CODE(MANIFEST_UNKNOWN_FILE_EXT);
DEFINE_RESULT_CODE(MANIFEST_FAILED_TO_DETECT);

DEFINE_RESULT_CODE(GREPO_FOLDER_NO_INCLUDE, -300);

DEFINE_RESULT_CODE(CMDINIT_NO_URL, -400);
DEFINE_RESULT_CODE(CMDINIT_FAILED_FETCH_UNKNOWN_MANIFEST);

DEFINE_RESULT_CODE(GIT_GENERIC_ERROR, -500);
DEFINE_RESULT_CODE(GIT_UNKNOWN_PROTOCOL);
DEFINE_RESULT_CODE(GIT_RAW_INT_ERROR);
DEFINE_RESULT_CODE(GIT_ERROR_OPENING_REPO);
DEFINE_RESULT_CODE(GIT_RESET_TYPE_NOT_SET);
DEFINE_RESULT_CODE(GIT_RESET_TYPE_UNKNOWN);
DEFINE_RESULT_CODE(GIT_NO_BRANCH_FOUND);
DEFINE_RESULT_CODE(GIT_REPO_NOT_OPEN);

DEFINE_RESULT_CODE(CMD_INCORRECT_PARAMETERS_IN_CONTEXT, -600);
DEFINE_RESULT_CODE(CMD_INCORRECT_PARAMETERS_COMBINATION);
DEFINE_RESULT_CODE(CMD_MISSING_PARAMETERS);
DEFINE_RESULT_CODE(CMD_GENERIC_RAW_ERROR);

} // namespace esys::repo

namespace std
{

ESYSREPO_API ostream &operator<<(ostream &os, const esys::repo::ResultCode &result)
{
    return os;
}

} // namespace std
