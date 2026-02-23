/**
 * \file config/fido_config_parse_as.c
 *
 * \brief Parse an "as" statement from the input scanner.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

/* forward decls. */
static int create_username_string(
    char** str, int* type, const fido_token_details* details,
    fido_scanner* scanner);
static int create_group_string(
    char** str, int* type, const fido_token_details* details,
    fido_scanner* scanner);

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
    char** str, int* type, fido_scanner* scanner)
{
    int retval, token;
    fido_token_details details;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_as, str, type, scanner);

    /* read the as token. */
    token = fido_scanner_read_token(&details, scanner);
    if (FIDO_SCANNER_TOKEN_TYPE_EOF == token)
    {
        retval = FIDO_ERROR_UNEXPECTED_EOF;
        goto error_exit;
    }
    else if (FIDO_SCANNER_TOKEN_TYPE_KEYWORD_AS != token)
    {
        retval = FIDO_ERROR_UNEXPECTED_TOKEN;
        goto error_exit;
    }

    /* read a username or group. */
    token = fido_scanner_read_token(&details, scanner);
    if (FIDO_SCANNER_TOKEN_TYPE_EOF == token)
    {
        retval = FIDO_ERROR_UNEXPECTED_EOF;
    }
    else if (FIDO_SCANNER_TOKEN_TYPE_USERNAME == token)
    {
        retval = create_username_string(str, type, &details, scanner);
    }
    else if (FIDO_SCANNER_TOKEN_TYPE_GROUP == token)
    {
        retval = create_group_string(str, type, &details, scanner);
    }
    else
    {
        retval = FIDO_ERROR_UNEXPECTED_TOKEN;
    }

    if (0 != retval)
    {
        goto error_exit;
    }

    /* success. */
    goto done;

error_exit:
    *str = NULL;
    *type = 0;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_as, retval, str, type, scanner);

    return retval;
}

/**
 * \brief Create a username string from token details and a scanner.
 *
 * \param str               Pointer to the character pointer to receive the
 *                          created string on success.
 * \param type              Pointer to the variable where the type of string is
 *                          stored.
 * \param details           The token details to use for this extraction.
 * \param scanner           The scanner to use for this extraction.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
static int create_username_string(
    char** str, int* type, const fido_token_details* details,
    fido_scanner* scanner)
{
    int retval;
    char* tmp;
    size_t name_len = (details->end_index - details->begin_index) + 2;
    const char* input = scanner->original_input + details->begin_index;

    /* create the username. */
    tmp = (char*)malloc(name_len);
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* copy the username. */
    memcpy(tmp, input, name_len - 1);
    tmp[name_len - 1] = 0;

    /* success. */
    retval = 0;
    *str = tmp;
    *type = FIDO_CONFIG_AS_TYPE_USER;
    goto done;

done:
    return retval;
}

/**
 * \brief Create a group string from token details and a scanner.
 *
 * \param str               Pointer to the character pointer to receive the
 *                          created string on success.
 * \param type              Pointer to the variable where the type of string is
 *                          stored.
 * \param details           The token details to use for this extraction.
 * \param scanner           The scanner to use for this extraction.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
static int create_group_string(
    char** str, int* type, const fido_token_details* details,
    fido_scanner* scanner)
{
    int retval;
    char* tmp;
    size_t name_len = (details->end_index - details->begin_index) + 2;
    const char* input = scanner->original_input + details->begin_index;

    /* the name length should include the colon prefix for the group. */
    if (name_len <= 2)
    {
        retval = FIDO_ERROR_BAD_LENGTH;
        goto done;
    }

    /* skip the colon for the group. */
    input += 1;
    name_len -= 1;

    MODEL_ASSERT(name_len > 0);

    /* create the group. */
    tmp = (char*)malloc(name_len);
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* copy the group. */
    memcpy(tmp, input, name_len - 1);
    tmp[name_len - 1] = 0;

    /* success. */
    retval = 0;
    *str = tmp;
    *type = FIDO_CONFIG_AS_TYPE_GROUP;
    goto done;

done:
    return retval;
}
