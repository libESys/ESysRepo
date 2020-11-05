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

project(esysrepo_t CXX)

include_directories(
    ../../../../include
    )

add_definitions(-DESYSTEST_USE_ESYSTEST)

set(ESYSREPO_T_CXX_SOURCES
    esysrepo_t_prec.cpp
    main.cpp
    testcasectrl.cpp
)
    
set(ESYSREPO_T_GREPO_CXX_SOURCES
    ../grepo/test/readmanifest01_grepo.cpp
    ../grepo/test/readmanifest02_grepo.cpp
    ../grepo/test/writemanifest01_grepo.cpp
)

set(ESYSREPO_T_LIBGIT2_CXX_SOURCES
    ../libgit2/test/clonerepo01_libgit2.cpp
    ../libgit2/test/opengitrepo01_libgit2.cpp
)

add_executable(esysrepo_t 
    ${ESYSREPO_T_CXX_SOURCES}
    ${ESYSREPO_T_GREPO_CXX_SOURCES}
    ${ESYSREPO_T_LIBGIT2_CXX_SOURCES}
    )    
	
find_package(Boost 1.66 REQUIRED QUIET COMPONENTS
             date_time filesystem iostreams program_options thread)

target_link_libraries(esysrepo_t PUBLIC
    esysrepo
    Boost::date_time
    Boost::filesystem
    Boost::iostreams
    Boost::program_options
    Boost::thread
)

target_link_libraries(esysrepo_t PUBLIC esystest)

if(DEFINED ESYSTEST_USE_BOOST)
add_definitions(-DBOOST_ALL_DYN_LINK)
find_package(Boost 1.66 REQUIRED QUIET COMPONENTS
             unit_test_framework )
target_link_libraries(emdev_t PUBLIC
        Boost::unit_test_framework
)
endif()

