/**
 * \file config/fido_config_parse_add_variable.c
 *
 * \brief Parse an add variable statement from the input scanner.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

static int add_variable_create(
    fido_config_add_variable** var, fido_token_details* details,
    fido_scanner* scanner);

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
    fido_config_add_variable** var, fido_scanner* scanner)
{
    int retval, token;
    fido_token_details details;
    fido_config_add_variable* tmp_var = NULL;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_add_variable, var, scanner);

    /* read the env token. */
    token = fido_scanner_read_token(&details, scanner);
    if (FIDO_SCANNER_TOKEN_TYPE_EOF == token)
    {
        retval = FIDO_ERROR_UNEXPECTED_EOF;
        goto error_exit;
    }
    else if (FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ENV != token)
    {
        retval = FIDO_ERROR_UNEXPECTED_TOKEN;
        goto error_exit;
    }

    /* read the environment variable name. */
    token = fido_scanner_read_token(&details, scanner);
    if (FIDO_SCANNER_TOKEN_TYPE_EOF == token)
    {
        retval = FIDO_ERROR_UNEXPECTED_EOF;
        goto error_exit;
    }
    else if (FIDO_SCANNER_TOKEN_TYPE_ADD_VARIABLE != token)
    {
        retval = FIDO_ERROR_UNEXPECTED_TOKEN;
        goto error_exit;
    }

    /* create the add variable instance. */
    retval = add_variable_create(&tmp_var, &details, scanner);
    if (0 != retval)
    {
        goto error_exit;
    }

    /* success. */
    retval = 0;
    *var = tmp_var;
    tmp_var = NULL;
    goto done;

error_exit:
    *var = NULL;

done:
    if (NULL != tmp_var)
    {
        fido_config_add_variable_release(tmp_var);
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_add_variable, retval, var, scanner);

    return retval;
}

/**
 * \brief Create a \ref fido_config_add_variable instance from an add variable
 * token.
 *
 * \param var           Pointer to the add variable pointer to set to the
 *                      created instance on success.
 * \param details       The token details for this token.
 * \param scanner       The scanner to use to extract this variable.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
static int add_variable_create(
    fido_config_add_variable** var, fido_token_details* details,
    fido_scanner* scanner)
{
    int retval;
    char var_name[1024];
    size_t var_length = (details->end_index - details->begin_index) + 2;
    const char* input = scanner->original_input + details->begin_index;

    /* verify that the variable name is at least 2 characters. */
    if (var_length <= 2)
    {
        retval = FIDO_ERROR_BAD_LENGTH;
        goto error_exit;
    }

    /* skip the + symbol. */
    input += 1;
    var_length -= 1;

    MODEL_ASSERT(var_length > 1);

    /* verify that the variable length doesn't exceed the size of var_name. */
    if (var_length > sizeof(var_name))
    {
        retval = FIDO_ERROR_BAD_LENGTH;
        goto error_exit;
    }

    /* copy the variable name. */
    memcpy(var_name, input, var_length - 1);
    var_name[var_length - 1] = 0;

    /* create the add variable instance. */
    retval = fido_config_add_variable_create(var, var_name);
    if (0 != retval)
    {
        goto error_exit;
    }

    /* success. */
    goto done;

error_exit:
    *var = NULL;

done:
    return retval;
}
