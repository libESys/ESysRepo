/*!
 * \file esys/repo/autolink.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * __legal_e__
 * \endcond
 *
 */

#pragma once

#ifdef ESYS_LIB_NAME
#undef ESYS_LIB_NAME
#endif
#define ESYS_LIB_NAME esysrepo

#ifdef ESYS_LIB_VERSION
#undef ESYS_LIB_VERSION
#endif
#define ESYS_LIB_VERSION "0.1.0"

#if !defined(ESYSREPO_EXPORTS) && defined(_MSC_VER)
#include <esysmsvc/autolink.h>
#endif
