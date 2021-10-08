#
# cmake-format: off
# __legal_b__
#
# Copyright (c) 2020-2021 Michel Gillet
# Distributed under the wxWindows Library Licence, Version 3.1.
# (See accompanying file LICENSE_3_1.txt or
# copy at http://www.wxwidgets.org/about/licence)
#
# __legal_e__
# cmake-format: on
#

project(esysrepo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.66 REQUIRED COMPONENTS filesystem program_options system)

find_package(PkgConfig REQUIRED)
pkg_search_module(git2 libgit2 REQUIRED)

find_package(nlohmann_json 3.6.1 REQUIRED)

include_directories(.. ../../../include ${git2_INCLUDE_DIRS}
                    ${termcolor_DIR}/include)

set(ESYSREPO_CXX_SOURCES
    config.cpp
    configfile.cpp
    configfileimpl.cpp
    configfolder.cpp
    esysrepo_prec.cpp
    filesystem.cpp
    gitbase.cpp
    githelper.cpp
    gitmngr.cpp
    manifest.cpp
    progresscallbackbase.cpp
    sshbase.cpp)

set(ESYSREPO_CLI_CXX_SOURCES
    cli/app.cpp
    cli/appbase.cpp
    cli/cmd_cli.cpp
    cli/cmdhelp_cli.cpp
    cli/cmdinfo_cli.cpp
    cli/cmdinit_cli.cpp
    cli/cmdlist_cli.cpp
    cli/cmdmanifest_cli.cpp
    cli/cmdsync_cli.cpp
    cli/cmdstatus_cli.cpp
    cli/cmdversion_cli.cpp)

set(ESYSREPO_EXE_CXX_SOURCES
    exe/cmd.cpp
    exe/cmdhelp.cpp
    exe/cmdinfo.cpp
    exe/cmdinit.cpp
    exe/cmdlist.cpp
    exe/cmdmanifest.cpp
    exe/cmdstatus.cpp
    exe/cmdsync.cpp
    exe/cmdversion.cpp)

set(ESYSREPO_GIT_CXX_SOURCES
    git/branch_git.cpp
    git/branches_git.cpp
    git/commit.cpp
    git/diffdelta_git.cpp
    git/difffile_git.cpp
    git/filestatus_git.cpp
    git/progress_git.cpp
    git/remote_git.cpp
    git/repostatus_git.cpp
    git/status_git.cpp
    git/updatetip_git.cpp)

set(ESYSREPO_GITCMDLINE_CXX_SOURCES gitcmdline/git_cmdline.cpp)

set(ESYSREPO_GREPO_CXX_SOURCES grepo/manifest_grepo.cpp
                               grepo/manifestimpl_grepo.cpp)

set(ESYSREPO_LIBGIT2_CXX_SOURCES
    libgit2/git_libgit2.cpp libgit2/gitimpl_libgit2.cpp
    libgit2/guardassign_libgit2.cpp libgit2/guardrelease_libgit2.cpp
    libgit2/guardsrelease_libgit2.cpp libgit2/libgit2.cpp)

set(ESYSREPO_LIBSSH2_CXX_SOURCES libssh2/ssh_libssh2.cpp
                                 libssh2/sshimpl_libssh2.cpp)

set(ESYSREPO_MANIFEST_CXX_SOURCES
    manifest/file_manifest.cpp
    manifest/filebase_manifest.cpp
    manifest/fileerror_manifest.cpp
    manifest/format_manifest.cpp
    manifest/group_manifest.cpp
    manifest/groups_manifest.cpp
    manifest/kind_manifest.cpp
    manifest/loader_manifest.cpp
    manifest/loaderbase_manifest.cpp
    manifest/loaderesysrepo_manifest.cpp
    manifest/loadergitsuper_manifest.cpp
    manifest/loadergrepo_manifest.cpp
    manifest/location_manifest.cpp
    manifest/repository_manifest.cpp
    manifest/runtasks_manifest.cpp
    manifest/sync_manifest.cpp
    manifest/syncrepo_manifest.cpp
    manifest/syncrepos_manifest.cpp
    manifest/taskbase_manifest.cpp
    manifest/type_manifest.cpp
    manifest/workerthread_manifest.cpp
    manifest/xmlfile.cpp
    manifest/xmlfileimpl_manifest.cpp)

add_library(
  esysrepo SHARED
  ${ESYSREPO_CXX_SOURCES}
  ${ESYSREPO_CLI_CXX_SOURCES}
  ${ESYSREPO_EXE_CXX_SOURCES}
  ${ESYSREPO_GIT_CXX_SOURCES}
  ${ESYSREPO_GITCMDLINE_CXX_SOURCES}
  ${ESYSREPO_GREPO_CXX_SOURCES}
  ${ESYSREPO_LIBGIT2_CXX_SOURCES}
  ${ESYSREPO_LIBSSH2_CXX_SOURCES}
  ${ESYSREPO_MANIFEST_CXX_SOURCES})

set_property(TARGET esysrepo PROPERTY VERSION ${ESYSREPO_VERSION})
set_property(TARGET esysrepo PROPERTY SOVERSION ${ESYSREPO_VERSION_MAJOR})

target_compile_features(esysrepo PRIVATE cxx_std_17)

target_include_directories(esysrepo PUBLIC ../.. ../../../include)

target_link_libraries(
  esysrepo
  PRIVATE Boost::filesystem
          Boost::program_options
          Boost::system
          git2
          esysfile
          esyslog
          esyslog_spdlog
          msword2md)

target_link_libraries(esysrepo PRIVATE nlohmann_json::nlohmann_json)

install(TARGETS esysrepo LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
  DIRECTORY ../../../include/esys/repo/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/esys/repo
  FILES_MATCHING
  PATTERN "*.h*")

if(COMMAND add_clang_format_target)
  add_clang_format_target(esysrepo)
endif()

if(COMMAND add_clang_tidy_target)
  add_clang_tidy_target(esysrepo)
endif()

add_subdirectory(test)

if(ESYSREPO_COVERAGE)
  setup_target_for_coverage_lcov(
    NAME
    esysrepo_coverage
    BASE_DIRECTORY
    "../"
    EXECUTABLE
    esysrepo_t
    EXECUTABLE_ARGS
    -f
    JUNIT
    -k
    report.junit
    --no_result_code
    DEPENDENCIES
    esysrepo_t
    EXCLUDE
    "/usr/*include/*"
    "/*/extlib/*"
    "/*/test/*"
    "/*/esyslog/*"
    "/*/esystest/*"
    ${CMAKE_BINARY_DIR}/*)
endif()
