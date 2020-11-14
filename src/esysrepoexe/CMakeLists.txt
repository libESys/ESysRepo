project(esysrepoexe CXX)

find_package(Boost 1.66 REQUIRED QUIET COMPONENTS
             system filesystem program_options thread)

include_directories(
    ../../include
    )

set(ESYSREPOEXE_CXX_SOURCES
    esysrepoexe_prec.cpp
    esysrepoexe.cpp
    main.cpp
)

add_executable(esysrepoexe
    ${ESYSREPOEXE_CXX_SOURCES}
)

set_target_properties(esysrepoexe PROPERTIES PREFIX "")
set_target_properties(esysrepoexe PROPERTIES OUTPUT_NAME "esysrepo")

target_link_libraries(esysrepoexe PRIVATE
    Boost::filesystem
    Boost::program_options
    Boost::system
    esysrepo
)

install(TARGETS esysrepoexe
    DESTINATION bin
)
