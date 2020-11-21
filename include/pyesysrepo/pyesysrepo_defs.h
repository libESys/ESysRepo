/*!
 * \file pyesysrepo/pyesysrepo_defs.h
 * \brief Definitions needed for pyesysrepo
 *
 * \cond
 * __legal_b__
 *
 * __legal_e__
 * \endcond
 *
 */

#pragma once

#ifdef PYESYSREPO_EXPORTS
#define PYESYSREPO_API __declspec(dllexport)
#elif PYESYSREPO_USE
#define PYESYSREPO_API __declspec(dllimport)
#else
#define PYESYSREPO_API
#endif
