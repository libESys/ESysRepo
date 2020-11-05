#
# __legal_b__
#
# Copyright (c) 2020 Michel Gillet
# Distributed under the wxWindows Library Licence, Version 3.1.
# (See accompanying file LICENSE_3_1.txt or
# copy at http://www.wxwidgets.org/about/licence)
#
# __legal_e__
#

project (esysrepo CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.66 REQUIRED COMPONENTS filesystem system)

find_package(PkgConfig REQUIRED)
pkg_search_module(git2 libgit2 REQUIRED)

include_directories(
    ..
    ../../../include
    ${git2_INCLUDE_DIRS}
)

set(ESYSREPO_CXX_SOURCES
    esysrepo_prec.cpp
    gitbase.cpp
    manifest.cpp
)

set(ESYSREPO_GIT_CXX_SOURCES
    git/branch_git.cpp
    git/remote_git.cpp
)

set(ESYSREPO_GREPO_CXX_SOURCES
    grepo/manifest_grepo.cpp
    grepo/manifestimpl_grepo.cpp
)

set(ESYSREPO_LIBGIT2_CXX_SOURCES
    libgit2/git_libgit2.cpp
    libgit2/gitimpl_libgit2.cpp
    libgit2/guardrelease_libgit2.cpp
    libgit2/libgit2.cpp
)

set(ESYSREPO_MANIFEST_CXX_SOURCES
    manifest/location_manifest.cpp
    manifest/repository_manifest.cpp
)

add_library (esysrepo SHARED
    ${ESYSREPO_CXX_SOURCES}
    ${ESYSREPO_GIT_CXX_SOURCES}
    ${ESYSREPO_GREPO_CXX_SOURCES}
    ${ESYSREPO_LIBGIT2_CXX_SOURCES}
    ${ESYSREPO_MANIFEST_CXX_SOURCES}
)

target_include_directories ( esysrepo PUBLIC
    ../..
    ../../../include
)

target_link_libraries( esysrepo
    Boost::filesystem
    Boost::system
    git2
    esysfile
)        

if (COMMAND add_clang_format_target)
add_clang_format_target(esysrepo)
endif()

if (COMMAND add_clang_tidy_target)
add_clang_tidy_target(esysrepo)
endif()

add_subdirectory(test)
