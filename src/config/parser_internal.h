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
#include <fido/scanner.h>

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
 * \brief Create an empty \ref fido_config_role instance.
 *
 * \param role              Pointer to the role pointer to set to this
 *                          created instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_role_create_empty(fido_config_role** role);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_role_create_empty, fido_config_role** role)
        /* role points to a region of memory large enough to hold a role */
        /* pointer. */
        MODEL_CHECK_OBJECT_RW(role, sizeof(*role));
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_role_create_empty)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_role_create_empty, int retval, fido_config_role** role)
        /* on success... */
        if (0 == retval)
        {
            /* *role points to a valid role instance. */
            MODEL_ASSERT(property_fido_config_role_valid(*role));
            /* the as_user and as_group overrides are NULL. */
            MODEL_ASSERT(NULL == (*role)->as_user);
            MODEL_ASSERT(NULL == (*role)->as_group);
        }
        else
        {
            /* *role is NULL. */
            MODEL_ASSERT(NULL == (*role));
            /* the error code belongs to the error enumeration. */
            enum fido_error_code ec = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(ec));
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_role_create_empty)

/**
 * \brief Set the name of the role to the given value.
 *
 * \param role              The role for this operation.
 * \param name              The new name for this role.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_role_name_set(fido_config_role* role, const char* name);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_role_name_set, fido_config_role* role, const char* name)
        /* role is valid. */
        MODEL_ASSERT(property_fido_config_role_valid(role));
        /* name must be valid. */
        MODEL_ASSERT(NULL != name);
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_role_name_set)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_role_name_set, int retval, fido_config_role* role,
    const char* name)
        /* role remains valid. */
        MODEL_ASSERT(property_fido_config_role_valid(role));

        /* on success... */
        if (0 == retval)
        {
            /* name is set. */
            MODEL_ASSERT(NULL != role->name);
        }
        else
        {
            /* the error code belongs to the error enumeration. */
            enum fido_error_code ec = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(ec));
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_role_name_set)

/**
 * \brief Set the as user of the role to the given value.
 *
 * \param role              The role for this operation.
 * \param as_user           The new as_user for this role.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_role_as_user_set(fido_config_role* role, const char* as_user);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_role_as_user_set, fido_config_role* role, const char* as_user)
        /* role is valid. */
        MODEL_ASSERT(property_fido_config_role_valid(role));
        /* as_user must be valid. */
        MODEL_ASSERT(NULL != as_user);
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_role_as_user_set)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_role_as_user_set, int retval, fido_config_role* role,
    const char* as_user)
        /* role remains valid. */
        MODEL_ASSERT(property_fido_config_role_valid(role));

        /* on success... */
        if (0 == retval)
        {
            /* as_user is set. */
            MODEL_ASSERT(NULL != role->as_user);
        }
        else
        {
            /* the error code belongs to the error enumeration. */
            enum fido_error_code ec = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(ec));
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_role_as_user_set)

/**
 * \brief Set the as group of the role to the given value.
 *
 * \param role              The role for this operation.
 * \param as_group          The new as_group for this role.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_role_as_group_set(fido_config_role* role, const char* as_group);

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
/* Start of private methods.                                                  */
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
        /* arg does not currently point to a next. */
        MODEL_ASSERT(NULL == arg->next);
        /* arguments have not yet been finalized. */
        MODEL_ASSERT(!cmd->arguments_finalized);
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_command_add_argument)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_command_add_argument, fido_config_command* cmd,
    fido_config_command_argument* arg)
        /* cmd is valid. */
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

/**
 * \brief Add a command to a role instance.
 *
 * \param role              The role instance for this operation.
 * \param cmd               The command to add.
 */
void
fido_config_role_add_command(
    fido_config_role* role, fido_config_command* cmd);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_role_add_command,
    fido_config_role* role, fido_config_command* cmd)
        /* role is valid. */
        MODEL_ASSERT(property_fido_config_role_valid(role));
        /* cmd is valid. */
        MODEL_ASSERT(property_fido_config_command_valid(cmd));
        /* cmd does not currently point to a next. */
        MODEL_ASSERT(NULL == cmd->next);
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_role_add_command)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_role_add_command, fido_config_role* role,
    fido_config_command* cmd)
        /* role is valid. */
        MODEL_ASSERT(property_fido_config_role_valid(role));
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_role_add_command)

/**
 * \brief Add a variable to a role instance.
 *
 * \param role              The role instance for this operation.
 * \param var               The variable to add.
 */
void
fido_config_role_add_variable(
    fido_config_role* role, fido_config_add_variable* var);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_role_add_variable,
    fido_config_role* role, fido_config_add_variable* var)
        /* role is valid. */
        MODEL_ASSERT(property_fido_config_role_valid(role));
        /* var is valid. */
        MODEL_ASSERT(property_fido_config_add_variable_valid(var));
        /* var does not currently point to a next. */
        MODEL_ASSERT(NULL == var->next);
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_role_add_variable)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_role_add_variable, fido_config_role* role,
    fido_config_add_variable* var)
        /* role is valid. */
        MODEL_ASSERT(property_fido_config_role_valid(role));
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_role_add_variable)

/**
 * \brief Add a permission to a role instance.
 *
 * \param role              The role instance for this operation.
 * \param perm              The permission to add.
 */
void
fido_config_role_add_permission(
    fido_config_role* role, fido_config_permission* perm);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_role_add_permission,
    fido_config_role* role, fido_config_permission* perm)
        /* role is valid. */
        MODEL_ASSERT(property_fido_config_role_valid(role));
        /* perm is valid. */
        MODEL_ASSERT(property_fido_config_permission_valid(perm));
        /* perm does not currently point to a next. */
        MODEL_ASSERT(NULL == perm->next);
        /* permissions have not yet been finalized. */
        MODEL_ASSERT(!role->permissions_finalized);
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_role_add_permission)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_role_add_permission, fido_config_role* role,
    fido_config_permission* perm)
        /* role is valid. */
        MODEL_ASSERT(property_fido_config_role_valid(role));
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_role_add_permission)

/**
 * \brief Finalize permissions for a \ref fido_config_role instance.
 *
 * \param role              The role instance for this operation.
 */
void
fido_config_role_permissions_finalize(fido_config_role* role);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_role_permissions_finalize, fido_config_role* role)
        /* role is valid. */
        MODEL_ASSERT(property_fido_config_role_valid(role));
        /* permissions have not yet been finalized. */
        MODEL_ASSERT(!role->permissions_finalized);
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_role_permissions_finalize)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_role_permissions_finalize, fido_config_role* role)
        /* role is valid. */
        MODEL_ASSERT(property_fido_config_role_valid(role));
        /* permissions for role have been finalized. */
        MODEL_ASSERT(role->permissions_finalized);
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_role_permissions_finalize)

/**
 * \brief Add a role to a config instance.
 *
 * \param config            The config instance for this operation.
 * \param role              The role to add.
 */
void
fido_config_add_role(
    fido_config* config, fido_config_role* role);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_add_role, fido_config* config, fido_config_role* role)
        /* config is valid. */
        MODEL_ASSERT(property_fido_config_valid(config));
        /* role is valid. */
        MODEL_ASSERT(property_fido_config_role_valid(role));
        /* role does not currently point to a next. */
        MODEL_ASSERT(NULL == role->next);
        /* roles have not yet been finalized. */
        MODEL_ASSERT(!config->roles_finalized);
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_add_role)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_add_role, fido_config* config, fido_config_role* role)
        /* config is valid. */
        MODEL_ASSERT(property_fido_config_valid(config));
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_add_role)

/**
 * \brief Finalize roles for a \ref fido_config instance.
 *
 * \param config            The config instance for this operation.
 */
void
fido_config_roles_finalize(fido_config* config);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_roles_finalize, fido_config* config)
        /* config is valid. */
        MODEL_ASSERT(property_fido_config_valid(config));
        /* roles have not yet been finalized. */
        MODEL_ASSERT(!config->roles_finalized);
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_roles_finalize)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_roles_finalize, fido_config* config)
        /* config is valid. */
        MODEL_ASSERT(property_fido_config_valid(config));
        /* roles for config have been finalized. */
        MODEL_ASSERT(config->roles_finalized);
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_roles_finalize)

/**
 * \brief Parse a permission statement into a \ref fido_config_permission
 * instance.
 *
 * \param perm          Pointer to the permision pointer to set to the created
 *                      instance on success.
 * \param scanner       The scanner to use to parse this permission.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_parse_permission(
    fido_config_permission** perm, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_parse_permission, fido_config_permission** perm,
    fido_scanner* scanner)
        /* the perm pointer is valid. */
        MODEL_CHECK_OBJECT_RW(perm, sizeof(*perm));
        /* the scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_parse_permission)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_parse_permission, int retval, fido_config_permission** perm,
    fido_scanner* scanner)
        /* on success... */
        if (0 == retval)
        {
            /* the permission is valid. */
            MODEL_ASSERT(property_fido_config_permission_valid(*perm));
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* perm is set to NULL. */
            MODEL_ASSERT(NULL == *perm);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_parse_permission)

/**
 * \brief Parse a command statement into a \ref fido_config_command instance.
 *
 * \param cmd           Pointer to the command pointer to set to the created
 *                      instance on success.
 * \param scanner       The scanner to use to parse this command.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_parse_command(
    fido_config_command** cmd, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_parse_command, fido_config_command** cmd,
    fido_scanner* scanner)
        /* the cmd pointer is valid. */
        MODEL_CHECK_OBJECT_RW(cmd, sizeof(*cmd));
        /* the scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_parse_command)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_parse_command, int retval, fido_config_command** cmd,
    fido_scanner* scanner)
        /* on success... */
        if (0 == retval)
        {
            /* the command is valid. */
            MODEL_ASSERT(property_fido_config_command_valid(*cmd));
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* cmd is set to NULL. */
            MODEL_ASSERT(NULL == *cmd);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_parse_command)

/**
 * \brief Parse command arguments, adding them to the given command.
 *
 * \param cmd           The command for this operation.
 * \param str           The string containing command arguments, separated by
 *                      spaces.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_parse_command_arguments(
    fido_config_command* cmd, char* str);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_parse_command_arguments, fido_config_command* cmd,
    const char* str)
        /* the command is valid. */
        MODEL_ASSERT(property_fido_config_command_valid(cmd));
        /* the command arguments have not yet been finalized. */
        MODEL_ASSERT(!cmd->arguments_finalized);
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_parse_command_arguments)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_parse_command_arguments, int retval, fido_config_command* cmd,
    const char* str)
        /* on success... */
        if (0 == retval)
        {
            /* the command is valid. */
            MODEL_ASSERT(property_fido_config_command_valid(cmd));
            /* the command arguments have been finalized. */
            MODEL_ASSERT(cmd->arguments_finalized);
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_parse_command_arguments)

/**
 * \brief Parse an add_variable expression.
 *
 * \param var           Pointer to the add variable pointer to set to the
 *                      created instance on success.
 * \param scanner       The scanner to use to parse this add variable
 *                      expression.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_parse_add_variable(
    fido_config_add_variable** var, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_parse_add_variable, fido_config_add_variable** var,
    fido_scanner* scanner)
        /* the var pointer is valid. */
        MODEL_CHECK_OBJECT_RW(var, sizeof(*var));
        /* the scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_parse_add_variable)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_parse_add_variable, int retval, fido_config_add_variable** var,
    fido_scanner* scanner)
        /* on success... */
        if (0 == retval)
        {
            /* the command is valid. */
            MODEL_ASSERT(property_fido_config_add_variable_valid(*var));
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* var is set to NULL. */
            MODEL_ASSERT(NULL == *var);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_parse_add_variable)

/**
 * \brief Parse an as expression.
 *
 * \param str           Pointer to the pointer to store the username / group
 *                      string for this expression on success.
 * \param type          Output for the as type. \see fido_config_as_type.
 * \param scanner       The scanner to use to parse this as expression.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_parse_as(
    char** str, int* type, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_parse_as, char** str, int* type, fido_scanner* scanner)
        /* the str pointer is valid. */
        MODEL_CHECK_OBJECT_RW(str, sizeof(*str));
        /* the type pointer is valid. */
        MODEL_CHECK_OBJECT_RW(type, sizeof(*type));
        /* the scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_parse_as)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_parse_as, int retval, char** str, int* type,
    fido_scanner* scanner)
        /* on success... */
        if (0 == retval)
        {
            /* the string is set. */
            MODEL_ASSERT(NULL != *str);
            /* the type is valid. */
            enum fido_config_as_type ty = (enum fido_config_as_type)*type;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(ty));
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* str is set to NULL. */
            MODEL_ASSERT(NULL == *str);
            /* type is set to 0. */
            MODEL_ASSERT(0 == *type);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_parse_as)

/**
 * \brief Parse a role instance from a config stream.
 *
 * \param role          Pointer to the pointer to store the role instance on
 *                      success.
 * \param scanner       The scanner to use to parse this as expression.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_parse_role(
    fido_config_role** role, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_config_parse_role, fido_config_role** role, fido_scanner* scanner)
        /* the role pointer is valid. */
        MODEL_CHECK_OBJECT_RW(role, sizeof(*role));
        /* the scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_config_parse_role)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_config_parse_role, int retval, fido_config_role** role,
    fido_scanner* scanner)
        /* on success... */
        if (0 == retval)
        {
            /* the role is valid. */
            MODEL_ASSERT(property_fido_config_role_valid(*role));
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* role is set to NULL. */
            MODEL_ASSERT(NULL == *role);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_config_parse_role)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
