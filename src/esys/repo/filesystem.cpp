/*!
 * \file esys/repo/filesystem.cpp
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
#include "esys/repo/filesystem.h"

#if ESYSREPO_HAS_STD_FILESYSTEM
#include <filesystem>
#endif

#include <boost/filesystem.hpp>
#include <boost/version.hpp>

#if BOOST_VERSION <= 107100
#define ESYSREPO_BOOST_FILESYSTEM_HAS_RECUR 0
#else
#define ESYSREPO_BOOST_FILESYSTEM_HAS_RECUR 1
#endif

namespace esys::repo
{

namespace stdcpp
{

ESYSREPO_API int copy(const std::string &src, const std::string &dst, bool recursive)
{
#if ESYSREPO_HAS_STD_FILESYSTEM
    try
    {
        if (recursive)
            std::filesystem::copy(src, dst, std::filesystem::copy_options::recursive);
        else
            std::filesystem::copy(src, dst);
    }
    catch (std::exception &e)
    {
        return -1;
    }
    return 0;
#else
    return -1;
#endif
}

ESYSREPO_API int remove_all(const std::string &path)
{
#if ESYSREPO_HAS_STD_FILESYSTEM
    try
    {
        std::filesystem::remove_all(path);
    }
    catch (std::exception &e)
    {
        return -1;
    }
    return 0;
#else
    return -1;
#endif
}

} // namespace stdcpp

namespace boost_no_recur
{

ESYSREPO_API int copy(const std::string &src, const std::string &dst, bool recursive)
{
    if (!recursive)
    {
        try
        {
            boost::filesystem::copy(src, dst);
        }
        catch (std::exception &e)
        {
            return -1;
        }
        return 0;
    }

    boost::filesystem::directory_iterator it(src);

    try
    {
        while (it != boost::filesystem::directory_iterator{})
        {
            boost::filesystem::path copy_to = dst;
            copy_to /= it->path().filename();

            if (boost::filesystem::is_directory(*it))
            {
                if (!boost::filesystem::create_directory(copy_to.string())) return -1;
                int result = copy(it->path().string(), copy_to.string(), recursive);
                if (result < 0) return result;
            }
            else
            {
                boost::system::error_code ec;

                boost::filesystem::copy(*it, copy_to, ec);
                if (ec) return -1;
            }

            *it++;
        }
    }
    catch (std::exception &e)
    {
        return -1;
    }
    return 0;
}

} // namespace boost_no_recur

namespace boost_recur
{

ESYSREPO_API int copy(const std::string &src, const std::string &dst, bool recursive)
{
#if ESYSREPO_BOOST_FILESYSTEM_HAS_RECUR
    try
    {
        if (recursive)
            boost::filesystem::copy(src, dst, boost::filesystem::copy_options::recursive);
        else
            boost::filesystem::copy(src, dst);
    }
    catch (std::exception &e)
    {
        return -1;
    }
    return 0;
#else
    return -1;
#endif
}

} // namespace boost_recur

namespace boost_all
{

ESYSREPO_API int remove_all(const std::string &path)
{
    try
    {
        boost::filesystem::remove_all(path);
    }
    catch (std::exception &e)
    {
        return -1;
    }
    return 0;
}

} // namespace boost_all

namespace boost_no_all
{

ESYSREPO_API int remove_all(const std::string &path)
{
    boost::filesystem::directory_iterator it(path);
    boost::filesystem::file_status stat;
    boost::system::error_code ec;

    try
    {
        while (it != boost::filesystem::directory_iterator{})
        {
            if (boost::filesystem::is_directory(*it))
            {
                int result = boost_no_all::remove_all(it->path().string());
                if (result < 0) return result;
            }
            else
            {
                stat = boost::filesystem::status(it->path(), ec);

                if (ec == boost::system::error_code())
                {
                    if ((stat.permissions() & boost::filesystem::perms::others_write)
                        != boost::filesystem::perms::others_write)
                    {
                        boost::filesystem::permissions(*it,
                                                       stat.permissions() | boost::filesystem::perms::others_write);
                    }
                }

                try
                {
                    boost::filesystem::remove(*it);
                }
                catch (std::exception &e)
                {
                    return -1;
                }
            }
            *it++;
        }
        boost::filesystem::remove_all(path);
    }
    catch (std::exception &e)
    {
        return -1;
    }
    return 0;
}

ESYSREPO_API int move(const std::string &src, const std::string &dst, bool recursive)
{
    int result = copy(src, dst, recursive);
    if (result < 0) return -1;

    result = remove_all(src);
    if (result < 0) return -2;
    return 0;
}

} // namespace boost_no_all

ESYSREPO_API int move(const std::string &src, const std::string &dst, bool recursive)
{
    int result = copy(src, dst, recursive);
    if (result < 0) return -1;

    result = remove_all(src);
    if (result < 0) return -2;
    return 0;
}

} // namespace esys::repo
