/*!
 * \file esys/repo/esysrepo_defs.h
 * \brief Definitions needed for esysrepo
 *
 * \cond
 * __legal_b__
 *
 * __legal_e__
 * \endcond
 *
 */

#pragma once

#ifdef ESYSREPO_EXPORTS
#define ESYSREPO_API __declspec(dllexport)
#elif ESYSREPO_USE
#define ESYSREPO_API __declspec(dllimport)
#else
#define ESYSREPO_API
#endif

#include "esys/repo/autolink.h"
