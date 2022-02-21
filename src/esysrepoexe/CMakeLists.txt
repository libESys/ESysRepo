project(esysrepoexe CXX)

find_package(Boost 1.66 REQUIRED QUIET COMPONENTS system filesystem
                                                  program_options thread)

include_directories(../../include ${termcolor_DIR}/include)

set(ESYSREPOEXE_CXX_SOURCES esysrepoexe_prec.cpp main.cpp)

add_executable(esysrepoexe ${ESYSREPOEXE_CXX_SOURCES})

set_target_properties(esysrepoexe PROPERTIES PREFIX "")
set_target_properties(esysrepoexe PROPERTIES OUTPUT_NAME "esysrepo")

set(ACTIVATE_SCRIPTS_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/../esys/repo/*.sh")
set(ACTIVATE_SCRIPTS_OUTPUT "${CMAKE_BINARY_DIR}/bin/")

add_custom_command(
  TARGET esysrepoexe
  PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${ACTIVATE_SCRIPTS_INPUT}
          ${ACTIVATE_SCRIPTS_OUTPUT}
  COMMAND chmod 775 ${ACTIVATE_SCRIPTS_OUTPUT}/*.sh)

target_link_libraries(
  esysrepoexe PRIVATE Boost::filesystem Boost::program_options Boost::system
                      esyslog esysrepo)

install(TARGETS esysrepoexe DESTINATION bin)
