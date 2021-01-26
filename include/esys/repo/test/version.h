/*!
 * \file esysrepo/version.h
 * \brief Version info for esysrepo_t
 *
 * \cond
 * __legal_b__
 *
 * __legal_e__
 * \endcond
 *
 */

#pragma once

// Bump-up with each new version
#define ESYSREPO_T_MAJOR_VERSION 0
#define ESYSREPO_T_MINOR_VERSION 0
#define ESYSREPO_T_RELEASE_NUMBER 1
#define ESYSREPO_T_VERSION_STRING "esysrepo_t 0.0.1"

// Must be updated manually as well each time the version above changes
#define ESYSREPO_T_VERSION_NUM_DOT_STRING "0.0.1"
#define ESYSREPO_T_VERSION_NUM_STRING "0001"

// nothing should be updated below this line when updating the version

#define ESYSREPO_T_VERSION_NUMBER \
    (ESYSREPO_T_MAJOR_VERSION * 1000) + (ESYSREPO_T_MINOR_VERSION * 100) + ESYSREPO_T_RELEASE_NUMBER
#define ESYSREPO_T_BETA_NUMBER 1
#define ESYSREPO_T_VERSION_FLOAT                                                                       \
    ESYSREPO_T_MAJOR_VERSION + (ESYSREPO_T_MINOR_VERSION / 10.0) + (ESYSREPO_T_RELEASE_NUMBER / 100.0) \
        + (ESYSREPO_T_BETA_NUMBER / 10000.0)

// check if the current version is at least major.minor.release
#define ESYSREPO_T_CHECK_VERSION(major, minor, release)                                                                \
    (ESYSREPO_T_MAJOR_VERSION > (major) || (ESYSREPO_T_MAJOR_VERSION == (major) && ESYSREPO_T_MINOR_VERSION > (minor)) \
     || (ESYSREPO_T_MAJOR_VERSION == (major) && ESYSREPO_T_MINOR_VERSION == (minor)                                    \
         && ESYSREPO_T_RELEASE_NUMBER >= (release)))
