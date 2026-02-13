/**
 * \file fido/config.h
 *
 * \brief Config tree for fido.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/function_contracts.h>
#include <fido/function_decl.h>
#include <stddef.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Identifier type.
 */
enum fido_config_identifier_type
{
    /** \brief Group identifier. */
    FIDO_CONFIG_IDENTIFIER_TYPE_GROUP = 1,
    /** \brief Username identifier. */
    FIDO_CONFIG_IDENTIFIER_TYPE_USERNAME,
};

/**
 * \brief Permission type.
 */
enum fido_config_permission_type
{
    /** \brief Permit type. */
    FIDO_CONFIG_PERMISSION_TYPE_PERMIT = 1,
    /** \brief Deny type. */
    FIDO_CONFIG_PERMISSION_TYPE_DENY,
};

/**
 * \brief Argument type.
 */
enum fido_config_command_argument_type
{
    /** \brief Wildcard argument type. */
    FIDO_CONFIG_ARGUMENT_TYPE_WILDCARD = 1,
    /** \brief Prefix wildcard argument type. */
    FIDO_CONFIG_ARGUMENT_TYPE_PREFIX_WILDCARD,
    /** \brief Postfix wildcard argument type. */
    FIDO_CONFIG_ARGUMENT_TYPE_POSTFIX_WILDCARD,
};

/**
 * \brief Fido config permission record.
 */
typedef struct fido_config_permission fido_config_permission;
struct fido_config_permission
{
    fido_config_permission* next;
    char* identifier;
    int identifier_type;
    int permission_type;
};

/**
 * \brief Fido config command argument record.
 */
typedef struct fido_config_command_argument fido_config_command_argument;
struct fido_config_command_argument
{
    fido_config_command_argument* next;
    int argument_type;
    char* argument_match;
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
