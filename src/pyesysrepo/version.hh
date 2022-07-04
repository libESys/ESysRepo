// PySwig 0.1.0

/*!
 * \file esys/repo/version.h
 * \brief Version info for esysrepo
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
#define ESYSREPO_MAJOR_VERSION 0
#define ESYSREPO_MINOR_VERSION 0
#define ESYSREPO_RELEASE_NUMBER 1
#define ESYSREPO_VERSION_STRING "esysrepo 0.0.1"

// Must be updated manually as well each time the version above changes
#define ESYSREPO_VERSION_NUM_DOT_STRING "0.0.1"
#define ESYSREPO_VERSION_NUM_STRING "0001"

// nothing should be updated below this line when updating the version

#define ESYSREPO_VERSION_NUMBER \
    (ESYSREPO_MAJOR_VERSION * 1000) + (ESYSREPO_MINOR_VERSION * 100) + ESYSREPO_RELEASE_NUMBER
#define ESYSREPO_BETA_NUMBER 1
#define ESYSREPO_VERSION_FLOAT                                                                   \
    ESYSREPO_MAJOR_VERSION + (ESYSREPO_MINOR_VERSION / 10.0) + (ESYSREPO_RELEASE_NUMBER / 100.0) \
        + (ESYSREPO_BETA_NUMBER / 10000.0)

// check if the current version is at least major.minor.release
#define ESYSREPO_CHECK_VERSION(major, minor, release)                                                            \
    (ESYSREPO_MAJOR_VERSION > (major) || (ESYSREPO_MAJOR_VERSION == (major) && ESYSREPO_MINOR_VERSION > (minor)) \
     || (ESYSREPO_MAJOR_VERSION == (major) && ESYSREPO_MINOR_VERSION == (minor)                                  \
         && ESYSREPO_RELEASE_NUMBER >= (release)))
