/**
 * \file config/fido_config_parse_role.c
 *
 * \brief Parse a role from the input scanner.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

/* forward decls. */
static int extract_name_from_string(
    char** name, fido_token_details* details, fido_scanner* scanner);
static int create_role(
    fido_config_role** role, const char* name,
    const char* as_user, const char* as_group,
    fido_config_command** command_head,
    fido_config_add_variable** variable_head,
    fido_config_permission** permission_head);
static int parse_as(
    fido_scanner* scanner, char** as_user, char** as_group);
static int parse_command(
    fido_scanner* scanner, fido_config_command** command_head);
static int parse_env(
    fido_scanner* scanner, fido_config_add_variable** variable_head);
static int parse_permission(
    fido_scanner* scanner, fido_config_permission** permission_head);

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
    fido_config_role** role, fido_scanner* scanner)
{
    int retval, token;
    fido_token_details details;
    fido_config_role* tmp_role = NULL;
    char* name = NULL;
    char* as_user = NULL;
    char* as_group = NULL;
    bool done_parsing = false;
    fido_config_command* command_head = NULL;
    fido_config_add_variable* variable_head = NULL;
    fido_config_permission* permission_head = NULL;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_role, role, scanner);

    /* read the role keyword. */
    token = fido_scanner_read_token(&details, scanner);
    if (FIDO_SCANNER_TOKEN_TYPE_EOF == token)
    {
        retval = FIDO_ERROR_UNEXPECTED_EOF;
        goto done;
    }
    else if (FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ROLE != token)
    {
        retval = FIDO_ERROR_UNEXPECTED_TOKEN;
        goto done;
    }

    /* read the role name. */
    token = fido_scanner_read_token(&details, scanner);
    if (FIDO_SCANNER_TOKEN_TYPE_EOF == token)
    {
        retval = FIDO_ERROR_UNEXPECTED_EOF;
        goto done;
    }
    else if (FIDO_SCANNER_TOKEN_TYPE_STRING != token)
    {
        retval = FIDO_ERROR_UNEXPECTED_TOKEN;
        goto done;
    }

    /* extract the name from the string. */
    retval = extract_name_from_string(&name, &details, scanner);
    if (0 != retval)
    {
        goto done;
    }

    /* read the open brace. */
    token = fido_scanner_read_token(&details, scanner);
    if (FIDO_SCANNER_TOKEN_TYPE_EOF == token)
    {
        retval = FIDO_ERROR_UNEXPECTED_EOF;
        goto done;
    }
    else if (FIDO_SCANNER_TOKEN_TYPE_OPEN_BRACE != token)
    {
        retval = FIDO_ERROR_UNEXPECTED_TOKEN;
        goto done;
    }

    /* begin parse loop. */
    while (!done_parsing)
    {
        token = fido_scanner_peek_token(&details, scanner);
        switch (token)
        {
            case FIDO_SCANNER_TOKEN_TYPE_EOF:
                retval = FIDO_ERROR_UNEXPECTED_EOF;
                goto done;

            case FIDO_SCANNER_TOKEN_TYPE_CLOSE_BRACE:
                retval =
                    create_role(
                        &tmp_role, name, as_user, as_group,
                        &command_head, &variable_head, &permission_head);
                done_parsing = true;
                break;

            case FIDO_SCANNER_TOKEN_TYPE_KEYWORD_AS:
                retval = parse_as(scanner, &as_user, &as_group);
                if (0 != retval)
                {
                    goto done;
                }
                break;

            case FIDO_SCANNER_TOKEN_TYPE_KEYWORD_CMD:
                retval = parse_command(scanner, &command_head);
                if (0 != retval)
                {
                    goto done;
                }
                break;

            case FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ENV:
                retval = parse_env(scanner, &variable_head);
                if (0 != retval)
                {
                    goto done;
                }
                break;

            case FIDO_SCANNER_TOKEN_TYPE_KEYWORD_PERMIT:
            case FIDO_SCANNER_TOKEN_TYPE_KEYWORD_DENY:
                retval = parse_permission(scanner, &permission_head);
                if (0 != retval)
                {
                    goto done;
                }
                break;

            default:
                retval = FIDO_ERROR_UNEXPECTED_TOKEN;
                goto done;
        }
    }

    /* success. */
    retval = 0;
    *role = tmp_role;
    tmp_role = NULL;
    goto done;

done:
    if (NULL != tmp_role)
    {
        fido_config_role_release(tmp_role);
    }

    if (NULL != name)
    {
        free(name);
    }

    if (NULL != as_user)
    {
        free(as_user);
    }

    if (NULL != as_group)
    {
        free(as_group);
    }

    while (NULL != command_head)
    {
        fido_config_command* x = command_head->next;
        fido_config_command_release(command_head);
        command_head = x;
    }

    while (NULL != variable_head)
    {
        fido_config_add_variable* x = variable_head->next;
        fido_config_add_variable_release(variable_head);
        variable_head = x;
    }

    while (NULL != permission_head)
    {
        fido_config_permission* x = permission_head->next;
        fido_config_permission_release(permission_head);
        permission_head = x;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_role, retval, role, scanner);

    return retval;
}

/**
 * \brief Extract a name from a string, ignoring escapes.
 *
 * \param name              Pointer to the character pointer to hold the
 *                          extracted name on success.
 * \param details           The token details used for extracting this string.
 * \param scanner           The scanner used for extracting this string.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
static int extract_name_from_string(
    char** name, fido_token_details* details, fido_scanner* scanner)
{
    int retval;
    char* tmp;
    size_t string_len = (details->end_index - details->begin_index) + 2;
    const char* input = scanner->original_input + details->begin_index;

    /* the string length should include the two quotes at the beginning and
     * end. */
    if (string_len <= 2)
    {
        retval = FIDO_ERROR_BAD_LENGTH;
        goto done;
    }

    /* skip the begin quote. */
    input += 1;
    string_len -= 1;

    /* skip the end quote. */
    string_len -= 1;

    MODEL_ASSERT(string_len > 0);

    /* allocate memory for the string. */
    tmp = malloc(string_len);
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* copy the string. */
    memcpy(tmp, input, string_len - 1);
    tmp[string_len - 1] = 0;

    /* success. */
    *name = tmp;
    retval = 0;
    goto done;

done:
    return retval;
}

/**
 * \brief Parse an "as" expression, updating the appropriate string.
 *
 * \param scanner           The scanner for this operation.
 * \param as_user           Pointer to the user string pointer.
 * \param as_group          Pointer to the group string pointer.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
static int parse_as(
    fido_scanner* scanner, char** as_user, char** as_group)
{
    int retval;
    char* str = NULL;
    int type;

    /* attempt to parse the as expression. */
    retval = fido_config_parse_as(&str, &type, scanner);
    if (0 != retval)
    {
        goto done;
    }

    /* decode the type. */
    switch (type)
    {
        case FIDO_CONFIG_IDENTIFIER_TYPE_USERNAME:
            if (NULL != *as_user)
            {
                retval = FIDO_ERROR_DUPLICATE_AS_USERNAME;
                goto cleanup_str;
            }
            *as_user = str;
            str = NULL;
            goto done;

        case FIDO_CONFIG_IDENTIFIER_TYPE_GROUP:
            if (NULL != *as_group)
            {
                retval = FIDO_ERROR_DUPLICATE_AS_GROUP;
                goto cleanup_str;
            }
            *as_group = str;
            str = NULL;
            goto done;

        default:
            retval = FIDO_ERROR_UNKNOWN_AS_TYPE;
            goto cleanup_str;
    }

cleanup_str:
    free(str);

done:
    return retval;
}

/**
 * \brief Parse command, adding this to the head of the command list.
 *
 * \param scanner               The scanner for this operation.
 * \param command_head          The head of the command list.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
static int parse_command(
    fido_scanner* scanner, fido_config_command** command_head)
{
    int retval;
    fido_config_command* tmp;

    /* parse the command. */
    retval = fido_config_parse_command(&tmp, scanner);
    if (0 != retval)
    {
        goto done;
    }

    /* Success: update the command list. */
    tmp->next = *command_head;
    *command_head = tmp;
    retval = 0;
    goto done;

done:
    return retval;
}

/**
 * \brief Parse a variable, adding this to the head of the variable list.
 *
 * \param scanner               The scanner for this operation.
 * \param variable_head         The head of the variable list.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
static int parse_env(
    fido_scanner* scanner, fido_config_add_variable** variable_head)
{
    int retval;
    fido_config_add_variable* tmp;

    /* parse the add variable. */
    retval = fido_config_parse_add_variable(&tmp, scanner);
    if (0 != retval)
    {
        goto done;
    }

    /* Success: update the variable list. */
    tmp->next = *variable_head;
    *variable_head = tmp;
    retval = 0;
    goto done;

done:
    return retval;
}

/**
 * \brief Parse a permission, adding this to the head of the permission list.
 *
 * \param scanner               The scanner for this operation.
 * \param permission_head       The head of the permission list.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
static int parse_permission(
    fido_scanner* scanner, fido_config_permission** permission_head)
{
    int retval;
    fido_config_permission* tmp;

    /* parse the permission. */
    retval = fido_config_parse_permission(&tmp, scanner);
    if (0 != retval)
    {
        goto done;
    }

    /* Success: update the permission list. */
    tmp->next = *permission_head;
    *permission_head = tmp;
    retval = 0;
    goto done;

done:
    return retval;
}

/* TODO - move these to a configurable header option. */
#define FIDO_DEFAULT_AS_USER "root"
#define FIDO_DEFAULT_AS_GROUP "wheel"

/**
 * \brief Create a role instance with the given name, as_user, as_group,
 * commands, variables, and permissions.
 *
 * \param role              Pointer to the role pointer to update with the
 *                          created role instance on success.
 * \param name              The name of this role.
 * \param as_user           The as_user name for this instance or NULL.
 * \param as_group          The as_group name for this instance or NULL.
 * \param command_head      Head of the command list.
 * \param variable_head     Head of the variable list.
 * \param permission_head   Head of the reversed permission list.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
static int create_role(
    fido_config_role** role, const char* name,
    const char* as_user, const char* as_group,
    fido_config_command** command_head,
    fido_config_add_variable** variable_head,
    fido_config_permission** permission_head)
{
    int retval;
    fido_config_role* tmp;

    /* set the as_user to the default if unset. */
    if (NULL == as_user)
    {
        as_user = FIDO_DEFAULT_AS_USER;
    }

    /* set the as_group to the default if unset. */
    if (NULL == as_group)
    {
        as_group = FIDO_DEFAULT_AS_GROUP;
    }

    /* create the role. */
    retval = fido_config_role_create(&tmp, name, as_user, as_group);
    if (0 != retval)
    {
        goto done;
    }

    /* assign the commands. */
    tmp->command_head = *command_head;
    *command_head = NULL;

    /* assign the variables. */
    tmp->variable_head = *variable_head;
    *variable_head = NULL;

    /* assign the permissions. */
    tmp->permission_head = *permission_head;
    *permission_head = NULL;
    fido_config_role_permissions_finalize(tmp);

    /* success. */
    *role = tmp;
    retval = 0;
    goto done;

done:
    return retval;
}
