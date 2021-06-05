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

project(esysrepo_t CXX)

include(GNUInstallDirs)
include(FindPkgConfig)

# add_definitions(-DESYSTEST_USE_ESYSTEST)
add_definitions(-DESYSTEST_MULTIOS -DESYSTEST_USE_BOOST)
set(ESYSTEST_USE_BOOST 1)

pkg_check_modules(LIBSSH2 libssh2 REQUIRED)

include_directories(
    ../../../../include
    ${LIBSSH2_INCLUDE_DIRS}
    )

set(ESYSREPO_T_CXX_SOURCES
    configfilewrite01.cpp
    configfoldercreate01.cpp
    esysrepo_t_prec.cpp
    main.cpp
    testcasectrl.cpp
)

set(ESYSREPO_T_CLI_CXX_SOURCES
    ../cli/test/app01.cpp
    ../cli/test/appbase01.cpp
    ../cli/test/cmdinfo01_cli.cpp
    ../cli/test/cmdinit01_cli.cpp
    ../cli/test/cmdlist01_cli.cpp
    ../cli/test/cmdmanifest01_cli.cpp
    ../cli/test/cmdstatus01_cli.cpp
    ../cli/test/cmdsync01_cli.cpp
)

set(ESYSREPO_T_EXE_CXX_SOURCES
    ../exe/test/cmdinit01.cpp
    ../exe/test/cmdmanifest01.cpp
    ../exe/test/cmdstatus01.cpp
    ../exe/test/cmdsync01.cpp
    ../exe/test/cmdsync02.cpp
    ../exe/test/cmdsync03.cpp
    ../exe/test/cmdsync04.cpp
    ../exe/test/cmdsync05.cpp
    ../exe/test/cmdsync06.cpp
    ../exe/test/cmdsync07.cpp
    ../exe/test/cmdsync08.cpp
    ../exe/test/fixcmd.cpp
)

set(ESYSREPO_T_GIT_CXX_SOURCES
    ../git/test/sortbranches01.cpp
)

set(ESYSREPO_T_GREPO_CXX_SOURCES
    ../grepo/test/readmanifest01_grepo.cpp
    ../grepo/test/readmanifest02_grepo.cpp
    ../grepo/test/readmanifest03_grepo.cpp
    ../grepo/test/writemanifest01_grepo.cpp
)

set(ESYSREPO_T_LIBGIT2_CXX_SOURCES
    ../libgit2/test/clonerepo01_libgit2.cpp
    ../libgit2/test/clonerepo02_libgit2.cpp
    ../libgit2/test/getparentcommit01_libgit2.cpp
    ../libgit2/test/getstatus01_libgit2.cpp
    ../libgit2/test/isdirty01_libgit2.cpp
    ../libgit2/test/opengitrepo01_libgit2.cpp
    ../libgit2/test/sshagent01.cpp
)

set(ESYSREPO_T_MANIFEST_CXX_SOURCES
    ../manifest/test/globymatch01.cpp
    ../manifest/test/task_t01_manifest.cpp
    ../manifest/test/xmlfileread01_manifest.cpp
    ../manifest/test/xmlfilewrite01_manifest.cpp
)

add_executable(esysrepo_t
    ${ESYSREPO_T_CXX_SOURCES}
    ${ESYSREPO_T_CLI_CXX_SOURCES}
    ${ESYSREPO_T_EXE_CXX_SOURCES}
    ${ESYSREPO_T_GIT_CXX_SOURCES}
    ${ESYSREPO_T_GREPO_CXX_SOURCES}
    ${ESYSREPO_T_LIBGIT2_CXX_SOURCES}
    ${ESYSREPO_T_MANIFEST_CXX_SOURCES}
    )

find_package(Boost 1.66 REQUIRED QUIET COMPONENTS
             date_time filesystem iostreams program_options thread)

target_link_libraries(esysrepo_t PUBLIC
    Boost::date_time
    Boost::filesystem
    Boost::iostreams
    Boost::program_options
    Boost::thread
    ${LIBSSH2_LIBRARIES}
    esysrepo
    esyslog
)

target_link_libraries(esysrepo_t PUBLIC esystest)

install(TARGETS esysrepo_t LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY ../../../../res/esysrepo_t DESTINATION share
    PATTERN "../../../../res/esysrepo_t/*"
)

add_test(NAME esysrepo_t
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND esysrepo_t -l test_suite
)

if(DEFINED ESYSTEST_USE_BOOST)
add_definitions(-DBOOST_ALL_DYN_LINK)
find_package(Boost 1.66 REQUIRED QUIET COMPONENTS
             unit_test_framework )
target_link_libraries(esysrepo_t PUBLIC
        Boost::unit_test_framework
)
endif()
