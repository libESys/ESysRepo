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
find_package(Poco 1.6.1 REQUIRED COMPONENTS Foundation)
find_package(nlohmann_json 3.6.1 REQUIRED)

include_directories(.. ../../../include ${termcolor_DIR}/include)

if(ESYSREPO_SNAP_BUILD)
  add_compile_definitions(ESYSREPO_SNAP_BUILD)
endif()

set(ESYSREPO_PUB_HEADERS
    autolink.h
    cmdlineapp.h
    config_defs.h
    configfile.h
    configfolder.h
    config.h
    esysrepo_defs.h
    esysrepo_prec.h
    filesystem.h
    gitbase.h
    git.h
    githelper.h
    gitmngr.h
    manifestfilebase.h
    manifest.h
    progresscallbackbase.h
    progresscallback_t.h
    queuemt.h
    sshbase.h
    ssh.h
    version.h)
list(TRANSFORM ESYSREPO_PUB_HEADERS
     PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/esys/repo/)

set(ESYSREPO_PRIV_HEADERS configfileimpl.h)
list(TRANSFORM ESYSREPO_PRIV_HEADERS PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

set(ESYSREPO_CXX_SOURCES
    config.cpp
    configfile.cpp
    configfileimpl.cpp
    configfolder.cpp
    errorinfo.cpp
    esysrepo_prec.cpp
    filesystem.cpp
    gitbase.cpp
    githelper.cpp
    gitmngr.cpp
    manifest.cpp
    progresscallbackbase.cpp
    result.cpp
    resultcode.cpp
    sshbase.cpp)

set(ESYSREPO_CLI_PUB_HEADERS
    cli/appbase.h
    cli/app.h
    cli/cmd.h
    cli/cmdenv.h
    cli/cmdhelp.h
    cli/cmdinfo.h
    cli/cmdinit.h
    cli/cmdlist.h
    cli/cmdmanifest.h
    cli/cmdstatus.h
    cli/cmdsync.h
    cli/cmd_t.h
    cli/cmdversion.h)

list(TRANSFORM ESYSREPO_CLI_PUB_HEADERS
     PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/esys/repo/)

set(ESYSREPO_CLI_CXX_SOURCES
    cli/app.cpp
    cli/appbase.cpp
    cli/cmd_cli.cpp
    cli/cmdenv_cli.cpp
    cli/cmdhelp_cli.cpp
    cli/cmdinfo_cli.cpp
    cli/cmdinit_cli.cpp
    cli/cmdlist_cli.cpp
    cli/cmdmanifest_cli.cpp
    cli/cmdsync_cli.cpp
    cli/cmdstatus_cli.cpp
    cli/cmdversion_cli.cpp)

set(ESYSREPO_EXE_PUB_HEADERS
    exe/cmd.h
    exe/cmdenv.h
    exe/cmdhelp.h
    exe/cmdinfo.h
    exe/cmdinit.h
    exe/cmdlist.h
    exe/cmdmanifest.h
    exe/cmdstatus.h
    exe/cmdsync.h
    exe/cmdversion.h)

list(TRANSFORM ESYSREPO_EXE_PUB_HEADERS
     PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/esys/repo/)

set(ESYSREPO_EXE_CXX_SOURCES
    exe/cmd.cpp
    exe/cmdenv.cpp
    exe/cmdhelp.cpp
    exe/cmdinfo.cpp
    exe/cmdinit.cpp
    exe/cmdlist.cpp
    exe/cmdmanifest.cpp
    exe/cmdstatus.cpp
    exe/cmdsync.cpp
    exe/cmdversion.cpp)

set(ESYSREPO_GIT_PUB_HEADERS
    git/branches.h
    git/branch.h
    git/branchtype.h
    git/commit.h
    git/commithash.h
    git/diff.h
    git/diffdelta.h
    git/diffdeltatype.h
    git/difffile.h
    git/fetchstep.h
    git/filestatus.h
    git/filemode.h
    git/mergeanalysisresult.h
    git/progress.h
    git/remote.h
    git/repostatus.h
    git/resettype.h
    git/status.h
    git/statussubtype.h
    git/statustype.h
    git/updatetip.h
    git/updatetiptype.h
    git/walkcommit.h)
list(TRANSFORM ESYSREPO_GIT_PUB_HEADERS
     PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/esys/repo/)

set(ESYSREPO_GIT_CXX_SOURCES
    git/branch_git.cpp
    git/branches_git.cpp
    git/commit.cpp
    git/commithash.cpp
    git/diff_git.cpp
    git/diffdelta_git.cpp
    git/difffile_git.cpp
    git/filestatus_git.cpp
    git/progress_git.cpp
    git/remote_git.cpp
    git/repostatus_git.cpp
    git/status_git.cpp
    git/updatetip_git.cpp
    git/walkcommit_git.cpp)

set(ESYSREPO_GITCMDLINE_PUB_HEADERS gitcmdline/git.h)

list(TRANSFORM ESYSREPO_GITCMDLINE_PUB_HEADERS
     PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/esys/repo/)

set(ESYSREPO_GITCMDLINE_CXX_SOURCES gitcmdline/git_cmdline.cpp)

set(ESYSREPO_GITSTATS_PUB_HEADERS
    gitstats/author.h
    gitstats/authormngr.h
    gitstats/basic.h
    gitstats/data.h
    gitstats/dataperiodauthor.h
    gitstats/dataperiod.h
    gitstats/datayear.h)

list(TRANSFORM ESYSREPO_GITSTATS_PUB_HEADERS
     PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/esys/repo/)

set(ESYSREPO_GITSTATS_CXX_SOURCES
    gitstats/author.cpp
    gitstats/authormngr.cpp
    gitstats/basic.cpp
    gitstats/data.cpp
    gitstats/dataperiodauthor.cpp
    gitstats/dataperiod.cpp
    gitstats/datayear.cpp)

set(ESYSREPO_GREPO_PUB_HEADERS grepo/manifest.h)
list(TRANSFORM ESYSREPO_GREPO_PUB_HEADERS
     PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/esys/repo/)

set(ESYSREPO_GREPO_PRIV_HEADERS grepo/manifestimpl.h)
list(TRANSFORM ESYSREPO_GREPO_PRIV_HEADERS PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

set(ESYSREPO_GREPO_CXX_SOURCES grepo/manifest_grepo.cpp
                               grepo/manifestimpl_grepo.cpp)

set(ESYSREPO_LIBGIT2_PUB_HEADERS libgit2/git.h)
list(TRANSFORM ESYSREPO_LIBGIT2_PUB_HEADERS
     PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/esys/repo/)

set(ESYSREPO_LIBGIT2_PRIV_HEADERS
    libgit2/gitimpl.h
    libgit2/guardassign.h
    libgit2/guard.h
    libgit2/guardrelease.h
    libgit2/guards.h
    libgit2/guardsrelease.h
    libgit2/libgit2.h)
list(TRANSFORM ESYSREPO_LIBGIT2_PRIV_HEADERS
     PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

set(ESYSREPO_LIBGIT2_CXX_SOURCES
    libgit2/git_libgit2.cpp libgit2/gitimpl_libgit2.cpp
    libgit2/guardassign_libgit2.cpp libgit2/guardrelease_libgit2.cpp
    libgit2/guardsrelease_libgit2.cpp libgit2/libgit2.cpp)

set(ESYSREPO_LIBSSH2_PUB_HEADERS libssh2/ssh.h)
list(TRANSFORM ESYSREPO_LIBSSH2_PUB_HEADERS
     PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/esys/repo/)

set(ESYSREPO_LIBSSH2_PRIV_HEADERS libssh2/sshimpl.h)
list(TRANSFORM ESYSREPO_LIBSSH2_PRIV_HEADERS
     PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

set(ESYSREPO_LIBSSH2_CXX_SOURCES libssh2/ssh_libssh2.cpp
                                 libssh2/sshimpl_libssh2.cpp)

set(ESYSREPO_MANIFEST_PUB_HEADERS
    manifest/base.h
    manifest/filebase.h
    manifest/fileerror.h
    manifest/file.h
    manifest/format.h
    manifest/group.h
    manifest/groups.h
    manifest/jsonfile.h
    manifest/kind.h
    manifest/loaderbase.h
    manifest/loaderesysrepo.h
    manifest/loadergitsuper.h
    manifest/loadergrepo.h
    manifest/loader.h
    manifest/location.h
    manifest/repository.h
    manifest/runtasks.h
    manifest/sync.h
    manifest/syncrepo.h
    manifest/syncrepos.h
    manifest/taskbase.h
    manifest/task_t.h
    manifest/type.h
    manifest/workerthread.h
    manifest/xmlfile.h)
list(TRANSFORM ESYSREPO_MANIFEST_PUB_HEADERS
     PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/esys/repo/)

set(ESYSREPO_MANIFEST_PRIV_HEADERS manifest/xmlfileimpl.h)
list(TRANSFORM ESYSREPO_MANIFEST_PRIV_HEADERS
     PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

set(ESYSREPO_MANIFEST_CXX_SOURCES
    manifest/base_manifest.cpp
    manifest/base_manifest.cpp
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
  ${ESYSREPO_PUB_HEADERS}
  ${ESYSREPO_PRIV_HEADERS}
  ${ESYSREPO_CXX_SOURCES}
  ${ESYSREPO_CLI_PUB_HEADERS}
  ${ESYSREPO_CLI_CXX_SOURCES}
  ${ESYSREPO_EXE_PUB_HEADERS}
  ${ESYSREPO_EXE_CXX_SOURCES}
  ${ESYSREPO_GIT_PUB_HEADERS}
  ${ESYSREPO_GIT_CXX_SOURCES}
  ${ESYSREPO_GITCMDLINE_PUB_HEADERS}
  ${ESYSREPO_GITCMDLINE_CXX_SOURCES}
  ${ESYSREPO_GITSTATS_PUB_HEADERS}
  ${ESYSREPO_GITSTATS_CXX_SOURCES}
  ${ESYSREPO_GREPO_PUB_HEADERS}
  ${ESYSREPO_GREPO_PRIV_HEADERS}
  ${ESYSREPO_GREPO_CXX_SOURCES}
  ${ESYSREPO_LIBGIT2_PUB_HEADERS}
  ${ESYSREPO_LIBGIT2_PRIV_HEADERS}
  ${ESYSREPO_LIBGIT2_CXX_SOURCES}
  ${ESYSREPO_LIBSSH2_PUB_HEADERS}
  ${ESYSREPO_LIBSSH2_PRIV_HEADERS}
  ${ESYSREPO_LIBSSH2_CXX_SOURCES}
  ${ESYSREPO_MANIFEST_PUB_HEADERS}
  ${ESYSREPO_MANIFEST_PRIV_HEADERS}
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
          Poco::Foundation
          esysfile
          esyslog
          esyslog_spdlog
          msword2md)

target_link_libraries(esysrepo PRIVATE nlohmann_json::nlohmann_json)

if(ESYSREPO_USE_CONAN)
  find_package(libgit2 REQUIRED)
  find_package(Libssh2 REQUIRED)

  target_link_libraries(esysrepo PRIVATE git2 ssh2)
else()
  find_package(PkgConfig REQUIRED)

  if(NOT ESYSREPO_USE_LOCAL_LIBGIT2)
    pkg_search_module(GIT2 REQUIRED IMPORTED_TARGET libgit2>=1.1.0)
    target_link_libraries(esysrepo PRIVATE PkgConfig::GIT2)
  else()
    target_link_libraries(esysrepo PRIVATE git2)
  endif()

  pkg_search_module(SSH2 REQUIRED IMPORTED_TARGET libssh2)
  target_link_libraries(esysrepo PRIVATE PkgConfig::SSH2)
endif()

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
  add_clang_tidy_target(
    esysrepo
    BASE_PATH
    ${ESYSREPO_DEV}
    HEADERS
    ${ESYSREPO_PUB_HEADERS}
    ${ESYSREPO_PRIV_HEADERS}
    ${ESYSREPO_CLI_PUB_HEADERS}
    ${ESYSREPO_EXE_PUB_HEADERS}
    ${ESYSREPO_GIT_PUB_HEADERS}
    ${ESYSREPO_GITCMDLINE_PUB_HEADERS}
    ${ESYSREPO_GREPO_PUB_HEADERS}
    ${ESYSREPO_GREPO_PRIV_HEADERS}
    ${ESYSREPO_LIBGIT2_PRIV_HEADERS}
    ${ESYSREPO_LIBGIT2_PUB_HEADERS}
    ${ESYSREPO_LIBSSH2_PRIV_HEADERS}
    ${ESYSREPO_LIBSSH2_PUB_HEADERS}
    ${ESYSREPO_MANIFEST_PRIV_HEADERS}
    ${ESYSREPO_MANIFEST_PUB_HEADERS})
endif()

add_subdirectory(test)

if(COMMAND add_valgrind_target)
  add_valgrind_target(esysrepo_t)
endif()

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

  add_custom_target(
    esysrepo_coverage-cleanup ALL
    COMMAND sed -i "s,${ESYSREPO_DEV}/,,g"
            ${CMAKE_CURRENT_BINARY_DIR}/esysrepo_coverage.info
    DEPENDS esysrepo_coverage
    COMMENT "esysrepo: Cleanup paths in esysrepo_coverage.info results"
    VERBATIM)
endif()
