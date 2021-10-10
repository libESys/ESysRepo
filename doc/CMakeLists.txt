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

set(DOXYGEN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
set(DOXYGEN_FILE_CMAKE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.cmake_doc)

# check if Doxygen is installed
find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYGEN_QUIET "NO")
  set(DOXYGEN_WARNINGS "YES")
  set(DOXYGEN_WARN_IF_UNDOCUMENTED "YES")
  set(DOXYGEN_WARN_IF_DOC_ERROR "YES")
  set(DOXYGEN_WARN_LOGFILE "")

  if(SUPERBUILD_BIN_SDK)
    set(DOXYGEN_QUIET "YES")
    set(DOXYGEN_WARNINGS "YES")
    set(DOXYGEN_WARN_IF_UNDOCUMENTED "YES")
    set(DOXYGEN_WARN_IF_DOC_ERROR "YES")
    set(DOXYGEN_WARN_LOGFILE "${CMAKE_CURRENT_BINARY_DIR}/doxygen.log")
  endif()

  set(TEMP_SED ${CMAKE_CURRENT_BINARY_DIR}/temp.sed)

  file(WRITE ${TEMP_SED} "s+$")
  file(APPEND ${TEMP_SED}
       "(ESYSREPO_DOC_OUTPUT_DIR)+${CMAKE_CURRENT_BINARY_DIR}+\n")
  file(APPEND ${TEMP_SED} "s+$")
  file(APPEND ${TEMP_SED} "(ESYSREPO)+${CMAKE_CURRENT_SOURCE_DIR}/..+\n")
  file(APPEND ${TEMP_SED} "s+$")
  file(APPEND ${TEMP_SED} "(DOXYGEN_QUIET)+${DOXYGEN_QUIET}+\n")
  file(APPEND ${TEMP_SED} "s+$")
  file(APPEND ${TEMP_SED} "(DOXYGEN_WARNINGS)+${DOXYGEN_WARNINGS}+\n")
  file(APPEND ${TEMP_SED} "s+$")
  file(APPEND ${TEMP_SED}
       "(DOXYGEN_WARN_IF_UNDOCUMENTED)+${DOXYGEN_WARN_IF_UNDOCUMENTED}+\n")
  file(APPEND ${TEMP_SED} "s+$")
  file(APPEND ${TEMP_SED}
       "(DOXYGEN_WARN_IF_DOC_ERROR)+${DOXYGEN_WARN_IF_DOC_ERROR}+\n")
  file(APPEND ${TEMP_SED} "s+$")
  file(APPEND ${TEMP_SED} "(DOXYGEN_WARN_LOGFILE)+${DOXYGEN_WARN_LOGFILE}+")
  add_custom_target(
    esysrepo_cmake_doc ALL
    COMMAND sed -f ${TEMP_SED} < ${DOXYGEN_FILE} > ${DOXYGEN_FILE_CMAKE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "ESysRepo: Generating Doxyfile.cmake_doc"
    VERBATIM)

  message("Doxygen build started")

  # note the option ALL which allows to build the docs together with the
  # application
  add_custom_target(
    esysrepo_doc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_FILE_CMAKE} # ${DOXYGEN_OUT}
    DEPENDS esysrepo_cmake_doc
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "ESysRepo: Generating API documentation with Doxygen"
    VERBATIM)

  if(SUPERBUILD_BIN_SDK)

    install(
      DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
      DESTINATION ${CMAKE_INSTALL_LIBDIR}/../doc/esysrepo
      COMPONENT doc)

  endif()
else(DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif(DOXYGEN_FOUND)

find_program(HUGO_BIN hugo)
if(HUGO_BIN)
  message("Hugo found: ${HUGO_BIN}")
  set(ESYSREPO_HUGO_PUBLIC_DIR $ENV{ESYSREPO_HUGO_PUBLIC_DIR})
  message(STATUS "ESYSREPO_HUGO_PUBLIC_DIR = ${ESYSREPO_HUGO_PUBLIC_DIR}")
  if(NOT ESYSREPO_HUGO_PUBLIC_DIR)
    set(ESYSREPO_HUGO_PUBLIC_DIR ${CMAKE_CURRENT_BINARY_DIR}/web/public)
  endif()
  message(STATUS "ESYSREPO_HUGO_PUBLIC_DIR = ${ESYSREPO_HUGO_PUBLIC_DIR}")
  message(
    STATUS
      "cd ${CMAKE_CURRENT_SOURCE_DIR}/web && ${HUGO_BIN} --themesDir ${ESYS_HUGO_THEME_DIR} -d ${ESYSREPO_HUGO_PUBLIC_DIR}"
  )

  add_custom_target(
    esysrepo_hugo ALL
    COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/web && ${HUGO_BIN} --themesDir
            ${ESYS_HUGO_THEME_DIR} -d ${ESYSREPO_HUGO_PUBLIC_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/web
    COMMENT "esysrepo: Generating web page"
    VERBATIM)

  add_custom_target(
    esysrepo_hugo_server ALL
    COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/web && ${HUGO_BIN} server -D
            --themesDir ${ESYS_HUGO_THEME_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/web
    COMMENT "esysrepo: start Hugo server"
    VERBATIM)

else()
  message(WARNING "Hugo not found")
endif(HUGO_BIN)
