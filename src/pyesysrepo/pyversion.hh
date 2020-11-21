// PySwig 0.0.1

/*!
 * \file pyesysrepo/version.h
 * \brief Version info for pyesysrepo
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
#define PYESYSREPO_MAJOR_VERSION 0
#define PYESYSREPO_MINOR_VERSION 1
#define PYESYSREPO_RELEASE_NUMBER 0
#define PYESYSREPO_VERSION_STRING "pyesysrepo 0.1.0"

// Must be updated manually as well each time the version above changes
#define PYESYSREPO_VERSION_NUM_DOT_STRING "0.1.0"
#define PYESYSREPO_VERSION_NUM_STRING "000100"

// nothing should be updated below this line when updating the version

#define PYESYSREPO_VERSION_NUMBER \
    (PYESYSREPO_MAJOR_VERSION * 1000) + (PYESYSREPO_MINOR_VERSION * 100) + PYESYSREPO_RELEASE_NUMBER
#define PYESYSREPO_BETA_NUMBER 1
#define PYESYSREPO_VERSION_FLOAT                                                                       \
    PYESYSREPO_MAJOR_VERSION + (PYESYSREPO_MINOR_VERSION / 10.0) + (PYESYSREPO_RELEASE_NUMBER / 100.0) \
        + (PYESYSREPO_BETA_NUMBER / 10000.0)

// check if the current version is at least major.minor.release
#define PYESYSREPO_CHECK_VERSION(major, minor, release)                                                                \
    (PYESYSREPO_MAJOR_VERSION > (major) || (PYESYSREPO_MAJOR_VERSION == (major) && PYESYSREPO_MINOR_VERSION > (minor)) \
     || (PYESYSREPO_MAJOR_VERSION == (major) && PYESYSREPO_MINOR_VERSION == (minor)                                    \
         && PYESYSREPO_RELEASE_NUMBER >= (release)))
