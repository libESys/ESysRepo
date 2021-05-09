#
# __legal_b__
#
# Copyright (c) 2020-2021 Michel Gillet
# Distributed under the wxWindows Library Licence, Version 3.1.
# (See accompanying file LICENSE_3_1.txt or
# copy at http://www.wxwidgets.org/about/licence)
#
# __legal_e__
#

CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

option(ESYSREPO_BUILD_DOC "Build the documentation" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ESYSREPO_VERSION_MAJOR 0)
set(ESYSREPO_VERSION_MINOR 1)
set(ESYSREPO_VERSION_PATCH 0)
set(ESYSREPO_VERSION
    ${ESYSREPO_VERSION_MAJOR}.${ESYSREPO_VERSION_MINOR}.${ESYSREPO_VERSION_PATCH})

if (ESYSREPO_BUILD_DOC)
add_subdirectory(doc)
endif()

add_subdirectory(src)
