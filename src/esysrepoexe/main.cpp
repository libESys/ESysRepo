/*!
 * \file esysrepoexe/main.cpp
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esysrepoexe/esysrepoexe_prec.h"
#include "esysrepoexe/version.h"
#include "esysrepoexe/esysrepoexe.h"

#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << ESYSREPOEXE_VERSION_STRING << std::endl << std::endl;

    ESysRepoExe exe;
    int result = 0;

    exe.set_os(std::cout);
    exe.set_args(argc, argv);
    result = exe.parse_args();

    if (result < 0)
    {
        exe.print_help(std::cout);
        return -result;
    }

    return -exe.run();
}