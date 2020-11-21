/*!
 * \file pyesysrepo/pyesysrepo_dll.cpp
 * \brief Entry point for a DLL under windows
 *
 * \cond
 * __legal_b__
 *
 * __legal_e__
 * \endcond
 *
 */

#include "pyesysrepo/pyesysrepo_prec.h"
#include "pyesysrepo/pyesysrepo_defs.h"

#ifdef WIN32
PYESYSREPO_API BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH: break;
    }
    return TRUE;
}
#endif
