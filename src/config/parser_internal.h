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
int FN_DECL_MUST_CHECK
fido_config_permission_create(
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
int FN_DECL_MUST_CHECK
fido_config_command_argument_create(
    fido_config_command_argument** arg, int argument_type,
    const char* argument_match);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_command_argument_create, fido_config_command_argument** arg,
    int argument_type, const char* argument_match)
        /* arg points to a region of memory large enough to hold an arg */
        /* pointer. */
        MODEL_CHECK_OBJECT_RW(arg, sizeof(*arg));
        /* argument type is a valid enumeration value. */
        enum fido_config_command_argument_type at =
            (enum fido_config_command_argument_type)argument_type;
        MODEL_ASSERT(__CPROVER_enum_is_in_range(at));
        /* argument_match is valid. */
        MODEL_ASSERT(NULL != argument_match);
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_command_argument_create)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_command_argument_create, int retval,
    fido_config_command_argument** arg, int argument_type,
    const char* argument_match)
        /* on success... */
        if (0 == retval)
        {
            /* *arg points to a valid argument instance. */
            MODEL_ASSERT(property_fido_config_command_argument_valid(*arg));
        }
        else
        {
            /* *arg is NULL. */
            MODEL_ASSERT(NULL == (*arg));
            /* the error code belongs to the error enumeration. */
            enum fido_error_code ec = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(ec));
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_command_argument_create)

/**
 * \brief Release a \ref fido_config_command_argument instance.
 *
 * \param arg           The argument to release.
 */
void fido_config_command_argument_release(fido_config_command_argument* arg);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_command_argument_release, fido_config_command_argument* arg)
        /* arg points to a region of memory large enough to hold it. */
        MODEL_CHECK_OBJECT_RW(arg, sizeof(*arg));
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_command_argument_release)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_command_argument_release, fido_config_command_argument* arg)
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_command_argument_release)

/**
 * \brief Create a \ref fido_config_command instance.
 *
 * \param cmd               Pointer to the command pointer to set to this
 *                          created instance on success.
 * \param binary            Real path to the binary.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_command_create(fido_config_command** cmd, const char* binary);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_command_create, fido_config_command** cmd, const char* binary)
        /* cmd points to a region of memory large enough to hold a cmd */
        /* pointer. */
        MODEL_CHECK_OBJECT_RW(cmd, sizeof(*cmd));
        /* binary is valid. */
        MODEL_ASSERT(NULL != binary);
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_command_create)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_command_create, int retval, fido_config_command** cmd,
    const char* binary)
        /* on success... */
        if (0 == retval)
        {
            /* *cmd points to a valid command instance. */
            MODEL_ASSERT(property_fido_config_command_valid(*cmd));
        }
        else
        {
            /* *cmd is NULL. */
            MODEL_ASSERT(NULL == (*cmd));
            /* the error code belongs to the error enumeration. */
            enum fido_error_code ec = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(ec));
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_command_create)

/**
 * \brief Release a \ref fido_config_command instance.
 *
 * \param cmd           The command to release.
 */
void fido_config_command_release(fido_config_command* cmd);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_command_release, fido_config_command* cmd)
        /* cmd points to a region of memory large enough to hold it. */
        MODEL_CHECK_OBJECT_RW(cmd, sizeof(*cmd));
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_command_release)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_command_release, fido_config_command* cmd)
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_command_release)

/**
 * \brief Create a \ref fido_config_add_variable instance.
 *
 * \param var               Pointer to the variable pointer to set to this
 *                          created instance on success.
 * \param name              The name of the variable to add.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_add_variable_create(
    fido_config_add_variable** var, const char* name);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_add_variable_create, fido_config_add_variable** var,
    const char* name)
        /* var points to a region of memory large enough to hold a var */
        /* pointer. */
        MODEL_CHECK_OBJECT_RW(var, sizeof(*var));
        /* name is valid. */
        MODEL_ASSERT(NULL != name);
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_add_variable_create)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_add_variable_create, int retval, fido_config_add_variable** var,
    const char* name)
        /* on success... */
        if (0 == retval)
        {
            /* *var points to a valid add variable instance. */
            MODEL_ASSERT(property_fido_config_add_variable_valid(*var));
        }
        else
        {
            /* *var is NULL. */
            MODEL_ASSERT(NULL == (*var));
            /* the error code belongs to the error enumeration. */
            enum fido_error_code ec = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(ec));
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_add_variable_create)

/**
 * \brief Release a \ref fido_config_add_variable instance.
 *
 * \param var           The add variable instance to release.
 */
void fido_config_add_variable_release(fido_config_add_variable* var);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_add_variable_release, fido_config_add_variable* var)
        /* var points to a region of memory large enough to hold it. */
        MODEL_CHECK_OBJECT_RW(var, sizeof(*var));
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_add_variable_release)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_add_variable_release, fido_config_add_variable* var)
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_add_variable_release)

/**
 * \brief Create a \ref fido_config_role instance.
 *
 * \param role              Pointer to the role pointer to set to this
 *                          created instance on success.
 * \param name              The name of the role.
 * \param as_user           Optional "as user" attribute or NULL.
 * \param as_group          Optional "as group" attribute or NULL.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_role_create(
    fido_config_role** role, const char* name, const char* as_user,
    const char* as_group);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_role_create, fido_config_role** role, const char* name,
    const char* as_user, const char* as_group)
        /* role points to a region of memory large enough to hold a role */
        /* pointer. */
        MODEL_CHECK_OBJECT_RW(role, sizeof(*role));
        /* name is valid. */
        MODEL_ASSERT(NULL != name);
        /* as_user is valid. */
        MODEL_ASSERT(NULL != as_user);
        /* as_group is valid. */
        MODEL_ASSERT(NULL != as_group);
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_role_create)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_role_create, int retval, fido_config_role** role,
    const char* name, const char* as_user, const char* as_group)
        /* on success... */
        if (0 == retval)
        {
            /* *role points to a valid role instance. */
            MODEL_ASSERT(property_fido_config_role_valid(*role));
        }
        else
        {
            /* *role is NULL. */
            MODEL_ASSERT(NULL == (*role));
            /* the error code belongs to the error enumeration. */
            enum fido_error_code ec = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(ec));
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_role_create)

/**
 * \brief Release a \ref fido_config_role instance.
 *
 * \param role          The role instance to release.
 */
void fido_config_role_release(fido_config_role* role);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_role_release, fido_config_role* role)
        /* role points to a region of memory large enough to hold it. */
        MODEL_CHECK_OBJECT_RW(role, sizeof(*role));
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_role_release)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_role_release, fido_config_role* role)
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_role_release)

/**
 * \brief Create a \ref fido_config instance.
 *
 * \param config            Pointer to the config pointer to set to this
 *                          created instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_create(fido_config** config);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_create, fido_config** config)
        /* config points to a region of memory large enough to hold a config */
        /* pointer. */
        MODEL_CHECK_OBJECT_RW(config, sizeof(*config));
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_create)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_create, int retval, fido_config** config)
        /* on success... */
        if (0 == retval)
        {
            /* *role points to a valid config instance. */
            MODEL_ASSERT(property_fido_config_valid(*config));
        }
        else
        {
            /* *config is NULL. */
            MODEL_ASSERT(NULL == (*config));
            /* the error code belongs to the error enumeration. */
            enum fido_error_code ec = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(ec));
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_create)

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Add an argument to the \ref fido_config_command instance.
 *
 * \param cmd               The command instance for this operation.
 * \param arg               The argument to add.
 */
void
fido_config_command_add_argument(
    fido_config_command* cmd, fido_config_command_argument* arg);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_command_add_argument,
    fido_config_command* cmd, fido_config_command_argument* arg)
        /* cmd is valid. */
        MODEL_ASSERT(property_fido_config_command_valid(cmd));
        /* arg is valid. */
        MODEL_ASSERT(property_fido_config_command_argument_valid(arg));
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_command_add_argument)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_command_add_argument, fido_config_command* cmd,
    fido_config_command_argument* arg)
        /* cmd points to a valid command instance. */
        MODEL_ASSERT(property_fido_config_command_valid(cmd));
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_command_add_argument)

/**
 * \brief Finalize arguments for a \ref fido_config_command instance.
 *
 * \param cmd               The command instance for this operation.
 */
void
fido_config_command_arguments_finalize(fido_config_command* cmd);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_command_arguments_finalize, fido_config_command* cmd)
        /* cmd is valid. */
        MODEL_ASSERT(property_fido_config_command_valid(cmd));
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_command_arguments_finalize)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_command_arguments_finalize, fido_config_command* cmd)
        /* cmd is valid. */
        MODEL_ASSERT(property_fido_config_command_valid(cmd));
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_command_arguments_finalize)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
