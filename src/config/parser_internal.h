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
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int fido_config_permission_create(
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

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_permission_create, int retval, fido_config_permission** perm,
    const char* identifier, int identifier_type, int permission_type)
        /* on success... */
        if (0 == retval)
        {
            /* *perm points to a valid permission instance. */
            MODEL_ASSERT(property_fido_config_permission_valid(*perm));
        }
        else
        {
            /* *perm is NULL. */
            MODEL_ASSERT(NULL == (*perm));
            /* the error code belongs to the error enumeration. */
            enum fido_error_code ec = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(ec));
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_permission_create)

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

/**
 * \brief Create a \ref fido_command_argument instance.
 *
 * \param arg               Pointer to the argument pointer to set to this
 *                          created instance on success.
 * \param argument_type     The type of argument. \see \ref
 *                          fido_config_command_argument_type.
 * \param argument_match    The match expression for the argument.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int fido_config_command_argument_create(
    fido_config_command_argument** arg, int argument_type,
    const char* argument_match);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_command_argument_create, fido_config_command_argument** arg,
    int argument_type, const char* argument_match)
        /* perm points to a region of memory large enough to hold an arg */
        /* pointer. */
        MODEL_CHECK_OBJECT_RW(arg, sizeof(*arg));
        /* argument type is a valid enumeration value. */
        enum fido_config_command_argument_type at =
            (enum fido_config_command_argument_type)argument_type;
        MODEL_ASSERT(__CPROVER_enum_is_in_range(at));
        /* argument_match is valid. */
        MODEL_ASSERT(NULL != argument_match);
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_command_argument_create)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
