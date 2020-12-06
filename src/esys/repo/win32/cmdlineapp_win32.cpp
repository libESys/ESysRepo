/*!
 * \file esys/repo/win32/cmdlineapp_win32.cpp
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

#include "esys/repo/esysrepo_prec.h"
#include "esys/repo/win32/cmdlineapp.h"

#include <iostream>

namespace esys
{

namespace repo
{

namespace win32
{

std::unique_ptr<CmdLineApp> CmdLineApp::s_cmd_line_app;

CmdLineApp &CmdLineApp::get()
{
    if (s_cmd_line_app == nullptr) s_cmd_line_app = std::make_unique<CmdLineApp>();

    return *s_cmd_line_app.get();
}

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
        case CTRL_C_EVENT:
            // Handle the CTRL-C signal.
            std::cout << "CTRL+C" << std::endl;
            ExitProcess(1);
            return TRUE;

        case CTRL_CLOSE_EVENT:
            // CTRL-CLOSE: confirm that the user wants to exit.
            return TRUE;

        case CTRL_BREAK_EVENT:
            // Pass other signals to the next handler.
            return FALSE;

        case CTRL_LOGOFF_EVENT:
            // Pass other signals to the next handler.
            return FALSE;

        case CTRL_SHUTDOWN_EVENT:
            // Pass other signals to the next handler.
            return FALSE;

        default: return FALSE;
    }
}

CmdLineApp::CmdLineApp()
{
}

CmdLineApp::~CmdLineApp()
{
}

int CmdLineApp::init()
{
    BOOL result_b;

    SetProcessShutdownParameters(0x280, SHUTDOWN_NORETRY);

    result_b = SetConsoleCtrlHandler(CtrlHandler, TRUE);

    if (result_b) return 0;
    return -1;
}

} // namespace win32

} // namespace repo

} // namespace esys
