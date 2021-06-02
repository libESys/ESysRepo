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

#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << ESYSREPOEXE_VERSION_STRING << std::endl << std::endl;

    // auto logger_mngr = esys::log::Mngr::get();

    esys::repo::cli::App cli;
    cli.set_version(ESYSREPOEXE_VERSION_NUM_DOT_STRING);

    int result = 0;

    // exe.set_logger_mngr(logger_mngr);

    cli.set_os(std::cout);
    cli.set_args(argc, argv);
    result = cli.parse_args();

    if (result < 0)
    {
        cli.print_help(std::cout);
        return -result;
    }

    result = cli.run();
    return -result;
}
