#
# cmake-format: off
# __legal_b__
#
# Copyright (c) 2020-2022 Michel Gillet
# Distributed under the wxWindows Library Licence, Version 3.1.
# (See accompanying file LICENSE_3_1.txt or
# copy at http://www.wxwidgets.org/about/licence)
#
# __legal_e__
# cmake-format: on
#

cmake_minimum_required(VERSION 3.12)

option(ESYSREPO_BUILD_DOC "Build the documentation" OFF)
option(ESYSREPO_COVERAGE "Generate code coverage for unit tests" OFF)
option(ESYSREPO_USE_CONAN "Use conan package mamager" Off)
option(ESYSREPO_SNAP_BUILD "This is a snap package build" Off)

if(ESYSREPO_USE_CONAN)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup()
endif()

get_filename_component(ESYSREPO_DEV "${CMAKE_CURRENT_LIST_DIR}" REALPATH)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ESYSREPO_VERSION_MAJOR 0)
set(ESYSREPO_VERSION_MINOR 1)
set(ESYSREPO_VERSION_PATCH 0)
set(ESYSREPO_VERSION
    ${ESYSREPO_VERSION_MAJOR}.${ESYSREPO_VERSION_MINOR}.${ESYSREPO_VERSION_PATCH}
)

include(clang_tidy OPTIONAL)
include(valgrind OPTIONAL)

if(ESYSREPO_BUILD_DOC)
  add_subdirectory(doc)
endif()

add_subdirectory(src)
