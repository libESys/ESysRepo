/*!
 * \file esysrepo/version.h
 * \brief Version info for esysrepoexe
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
#define ESYSREPOEXE_MAJOR_VERSION 0
#define ESYSREPOEXE_MINOR_VERSION 1
#define ESYSREPOEXE_RELEASE_NUMBER 0
#define ESYSREPOEXE_VERSION_STRING "ESysRepo 0.1.0"

// Must be updated manually as well each time the version above changes
#define ESYSREPOEXE_VERSION_NUM_DOT_STRING "0.1.0"
#define ESYSREPOEXE_VERSION_NUM_STRING "000100"

// nothing should be updated below this line when updating the version

#define ESYSREPOEXE_VERSION_NUMBER \
    (ESYSREPOEXE_MAJOR_VERSION * 1000) + (ESYSREPOEXE_MINOR_VERSION * 100) + ESYSREPOEXE_RELEASE_NUMBER
#define ESYSREPOEXE_BETA_NUMBER 1
#define ESYSREPOEXE_VERSION_FLOAT                                                                         \
    ESYSREPOEXE_MAJOR_VERSION + (ESYSREPOEXE_MINOR_VERSION / 10.0) + (ESYSREPOEXE_RELEASE_NUMBER / 100.0) \
        + (ESYSREPOEXE_BETA_NUMBER / 10000.0)

// check if the current version is at least major.minor.release
#define ESYSREPOEXE_CHECK_VERSION(major, minor, release)                              \
    (ESYSREPOEXE_MAJOR_VERSION > (major)                                              \
     || (ESYSREPOEXE_MAJOR_VERSION == (major) && ESYSREPOEXE_MINOR_VERSION > (minor)) \
     || (ESYSREPOEXE_MAJOR_VERSION == (major) && ESYSREPOEXE_MINOR_VERSION == (minor) \
         && ESYSREPOEXE_RELEASE_NUMBER >= (release)))
