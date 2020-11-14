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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.66 REQUIRED COMPONENTS filesystem system)

find_package(PkgConfig REQUIRED)
pkg_search_module(git2 libgit2 REQUIRED)

find_package(nlohmann_json 3.6.1 REQUIRED)

include_directories(
    ..
    ../../../include
    ${git2_INCLUDE_DIRS}
)

set(ESYSREPO_CXX_SOURCES
    config.cpp
    configfile.cpp
    configfileimpl.cpp
    configfolder.cpp
    esysrepo_prec.cpp
    filesystem.cpp
    gitbase.cpp
    manifest.cpp
)

set(ESYSREPO_EXE_CXX_SOURCES
    exe/cmdinit.cpp
    exe/cmdsync.cpp
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
    manifest/clonerepos_manifest.cpp
    manifest/fetchbase_manifest.cpp
    manifest/fetchesysrepo_manifest.cpp
    manifest/fetchgitsuper_manifest.cpp
    manifest/fetchgrepo_manifest.cpp
    manifest/fetch_manifest.cpp
    manifest/file_manifest.cpp
    manifest/location_manifest.cpp
    manifest/repository_manifest.cpp
    manifest/type_manifest.cpp
    manifest/xmlfile.cpp
    manifest/xmlfileimpl_manifest.cpp
)

add_library (esysrepo SHARED
    ${ESYSREPO_CXX_SOURCES}
    ${ESYSREPO_EXE_CXX_SOURCES}
    ${ESYSREPO_GIT_CXX_SOURCES}
    ${ESYSREPO_GREPO_CXX_SOURCES}
    ${ESYSREPO_LIBGIT2_CXX_SOURCES}
    ${ESYSREPO_MANIFEST_CXX_SOURCES}
)

target_include_directories ( esysrepo PUBLIC
    ../..
    ../../../include
)

target_link_libraries( esysrepo PRIVATE
    Boost::filesystem
    Boost::system
    git2
    esysfile
)        

target_link_libraries(esysrepo PRIVATE nlohmann_json::nlohmann_json)

if (COMMAND add_clang_format_target)
add_clang_format_target(esysrepo)
endif()

if (COMMAND add_clang_tidy_target)
add_clang_tidy_target(esysrepo)
endif()

add_subdirectory(test)
