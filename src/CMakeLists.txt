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

if(ESYSREPO_COVERAGE)
  include(CodeCoverage)
  append_coverage_compiler_flags()
endif()

add_subdirectory(esys/repo)
add_subdirectory(esysrepoexe)
