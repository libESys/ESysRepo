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

#include <esys/repo/cli/app.h>

#include <termcolor/termcolor.hpp>

#include <iostream>

int main(int argc, char *argv[])
{
    int result = 0;
    esys::repo::cli::App cli;

    cli.setup_terminal();

    std::cout << termcolor::bold << ESYSREPOEXE_VERSION_STRING << termcolor::reset << std::endl
              << std::endl;

    cli.set_version(ESYSREPOEXE_VERSION_NUM_DOT_STRING);
    cli.set_os(std::cout);
    cli.set_args(argc, argv);
    result = cli.parse_and_configure();

    if (result < 0)
    {
        cli.print_help(std::cout);
        return -result;
    }

    result = cli.run();
    return -result;
}
