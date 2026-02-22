/**
 * \file fido/config.h
 *
 * \brief Config tree for fido.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/error_codes.h>
#include <fido/function_contracts.h>
#include <fido/function_decl.h>
#include <fido/model_assert.h>
#include <stdbool.h>
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
    /** \brief Verbatim argument type. */
    FIDO_CONFIG_ARGUMENT_TYPE_VERBATIM,
};

/**
 * \brief "as" type.
 */
enum fido_config_as_type
{
    /** \brief As user type. */
    FIDO_CONFIG_AS_TYPE_USER = 1,
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

/**
 * \brief Fido config command record.
 */
typedef struct fido_config_command fido_config_command;
struct fido_config_command
{
    fido_config_command* next;
    bool arguments_finalized;
    char* binary;
    fido_config_command_argument* head;
};

/**
 * \brief Fido config environment variable additions.
 */
typedef struct fido_config_add_variable fido_config_add_variable;
struct fido_config_add_variable
{
    fido_config_add_variable* next;
    char* name;
};

/**
 * \brief Fido config role.
 */
typedef struct fido_config_role fido_config_role;
struct fido_config_role
{
    fido_config_role* next;
    bool permissions_finalized;
    char* name;
    char* as_user;
    char* as_group;
    fido_config_command* command_head;
    fido_config_add_variable* variable_head;
    fido_config_permission* permission_head;
};

/**
 * \brief Fido config.
 */
typedef struct fido_config fido_config;
struct fido_config
{
    bool roles_finalized;
    fido_config_role* head;
};

/******************************************************************************/
/* Start of model checking properties.                                        */
/******************************************************************************/

/**
 * \brief Valid permission record property.
 *
 * \param perm          The permission record to check.
 *
 * \returns true if the permission record is valid.
 */
bool
property_fido_config_permission_valid(
    const fido_config_permission* perm);

/**
 * \brief Valid command argument property.
 *
 * \param arg           The command argument to check.
 *
 * \returns true if the command argument is valid.
 */
bool
property_fido_config_command_argument_valid(
    const fido_config_command_argument* arg);

/**
 * \brief Valid command record property.
 *
 * \param cmd           The command record to check.
 *
 * \returns true if the command record is valid.
 */
bool
property_fido_config_command_valid(
    const fido_config_command* cmd);

/**
 * \brief Finalized command record property.
 *
 * \param cmd           The command record to check.
 *
 * \returns true if the command record is finalized.
 */
bool
property_fido_config_command_finalized(
    const fido_config_command* cmd);

/**
 * \brief Valid add variable record.
 *
 * \param arg           The add variable record to check.
 *
 * \returns true if the add variable record is valid.
 */
bool
property_fido_config_add_variable_valid(
    const fido_config_add_variable* arg);

/**
 * \brief Valid role record.
 *
 * \param role          The role record to check.
 *
 * \returns true if the role record is valid.
 */
bool
property_fido_config_role_valid(
    const fido_config_role* role);

/**
 * \brief Finalized role record.
 *
 * \param role          The role record to check.
 *
 * \returns true if the role record is finalized.
 */
bool
property_fido_config_role_finalized(
    const fido_config_role* role);

/**
 * \brief Valid config record.
 *
 * \param config        The config record to check.
 *
 * \returns true if the config record is valid.
 */
bool
property_fido_config_valid(
    const fido_config* config);

/**
 * \brief Finalized config record.
 *
 * \param config        The config record to check.
 *
 * \returns true if the config record is finalized.
 */
bool
property_fido_config_finalized(
    const fido_config* config);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Release a \ref fido_config instance.
 *
 * \param config        The config record to release.
 */
void
fido_config_release(fido_config* config);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_release, fido_config* config)
        /* config points to a region of memory large enough to hold it. */
        MODEL_CHECK_OBJECT_RW(config, sizeof(*config));
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_release)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_release, fido_config* config)
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_release)

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Parse config data into a \ref fido_config instance.
 *
 * \param config        Pointer to the config pointer to set to the created
 *                      instance on success.
 * \param input         The input string to parse.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_parse(fido_config** config, const char* input);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_parse, fido_config** config, const char* input)
        /* the config pointer is valid. */
        MODEL_CHECK_OBJECT_RW(config, sizeof(*config));
        /* the input is not NULL. */
        MODEL_ASSERT(NULL != input);
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_parse)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_parse, int retval, fido_config** config, const char* input)
        /* on success... */
        if (0 == retval)
        {
            /* the config is valid. */
            MODEL_ASSERT(property_fido_config_valid(*config));
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* config is set to NULL. */
            MODEL_ASSERT(NULL == *config);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_parse)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
