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
 * \brief Create a \ref fido_config_permission instance.
 *
 * \param perm              Pointer to the permission pointer to set to this
                            created instance on success.
 * \param identifier        The identifier name.
 * \param identifier_type   The identifier type. \see
 *                          \ref fido_config_identifier_type.
 * \param permission_type   The permission type. \see
 *                          \ref fido_config_permission_type.
 */
void fido_config_permission_create(
    fido_config_permission** perm, const char* identifier, int identifier_type,
    int permission_type);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_permission_create, fido_config_permission** perm,
    const char* identifier, int identifier_type, int permission_type)
        /* perm points to a region of memory large enough to hold a perm */
        /* pointer. */
        MODEL_CHECK_OBJECT_RW(perm, sizeof(*perm));
        /* identifier is valid. */
        MODEL_ASSERT(NULL != identifier);
        /* identifier type is a valid enumeration value. */
        enum fido_config_identifier_type it =
            (enum fido_config_identifier_type)identifier_type;
        MODEL_ASSERT(__CPROVER_enum_is_in_range(it));
        /* permission type is a valid enumeration value. */
        enum fido_config_permission_type pt =
            (enum fido_config_permission_type)permission_type;
        MODEL_ASSERT(__CPROVER_enum_is_in_range(pt));
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_permission_create)

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
