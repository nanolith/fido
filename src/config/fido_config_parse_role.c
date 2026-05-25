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

/* TODO - move these to a configurable header option. */
#define FIDO_DEFAULT_AS_USER "root"
#define FIDO_DEFAULT_AS_GROUP "wheel"

/* forward decls. */
static int extract_name_from_string(
    char** name, fido_token_details* details, fido_scanner* scanner);

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
    bool done_parsing = false;

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

    /* create a role. */
    retval = fido_config_role_create(&tmp_role, name, NULL, NULL);
    if (0 != retval)
    {
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
                /* eat this token. */
                token = fido_scanner_read_token(&details, scanner);
                if (FIDO_SCANNER_TOKEN_TYPE_CLOSE_BRACE != token)
                {
                    retval = FIDO_ERROR_UNEXPECTED_TOKEN;
                    goto done;
                }
                done_parsing = true;
                break;

            case FIDO_SCANNER_TOKEN_TYPE_KEYWORD_AS:
                retval = fido_config_parse_role_as_clause(tmp_role, scanner);
                if (0 != retval)
                {
                    goto done;
                }
                break;

            case FIDO_SCANNER_TOKEN_TYPE_KEYWORD_CMD:
                retval = fido_config_parse_role_command(tmp_role, scanner);
                if (0 != retval)
                {
                    goto done;
                }
                break;

            case FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ENV:
                retval = fido_config_parse_role_variable(tmp_role, scanner);
                if (0 != retval)
                {
                    goto done;
                }
                break;

            case FIDO_SCANNER_TOKEN_TYPE_KEYWORD_PERMIT:
            case FIDO_SCANNER_TOKEN_TYPE_KEYWORD_DENY:
                retval = fido_config_parse_role_permission(tmp_role, scanner);
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

    /* set root if as-user not set. */
    if (NULL == tmp_role->as_user)
    {
        retval = fido_config_role_as_user_set(tmp_role, FIDO_DEFAULT_AS_USER);
        if (0 != retval)
        {
            goto done;
        }
    }

    /* set wheel if as-group not set. */
    if (NULL == tmp_role->as_group)
    {
        retval = fido_config_role_as_group_set(tmp_role, FIDO_DEFAULT_AS_GROUP);
        if (0 != retval)
        {
            goto done;
        }
    }

    /* finalize permissions. */
    fido_config_role_permissions_finalize(tmp_role);

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

    if (0 != retval)
    {
        *role = NULL;
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
