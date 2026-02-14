/**
 * \file config/parser_internal.h
 *
 * \brief Internal data structures and methods relating to the fido config
 * parser.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/config.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Release a \ref fido_config_permission instance.
 *
 * \param perm          The permission to release.
 */
void fido_config_permission_release(fido_config_permission* perm);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_permission_release, fido_config_permission* perm)
        /* perm points to a region of memory large enough to hold it. */
        MODEL_CHECK_OBJECT_RW(perm, sizeof(*perm));
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_permission_release)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_permission_release, fido_config_permission* perm)
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_permission_release)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
