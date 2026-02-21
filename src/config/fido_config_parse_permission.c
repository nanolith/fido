/**
 * \file config/fido_config_parse_permission.c
 *
 * \brief Parse a permission from the input scanner.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

/* forward decls. */
static int create_permission_with_username(
    fido_config_permission** perm, const fido_token_details* details,
    int permission_type, fido_scanner* scanner);
static int create_permission_with_group(
    fido_config_permission** perm, const fido_token_details* details,
    int permission_type, fido_scanner* scanner);

/**
 * \brief Parse config data into a \ref fido_config instance.
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
    fido_config_permission** perm, fido_scanner* scanner)
{
    int retval, token, permission_type;
    fido_token_details details;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_permission, perm, scanner);

    /* read the permit / deny token. */
    token = fido_scanner_read_token(&details, scanner);
    if (FIDO_SCANNER_TOKEN_TYPE_KEYWORD_PERMIT == token)
    {
        permission_type = FIDO_CONFIG_PERMISSION_TYPE_PERMIT;
    }
    else if (FIDO_SCANNER_TOKEN_TYPE_KEYWORD_DENY == token)
    {
        permission_type = FIDO_CONFIG_PERMISSION_TYPE_DENY;
    }
    else if (FIDO_SCANNER_TOKEN_TYPE_EOF == token)
    {
        retval = FIDO_ERROR_UNEXPECTED_EOF;
        goto error_exit;
    }
    else
    {
        retval = FIDO_ERROR_UNEXPECTED_TOKEN;
        goto error_exit;
    }

    /* read a username or group. */
    token = fido_scanner_read_token(&details, scanner);
    if (FIDO_SCANNER_TOKEN_TYPE_USERNAME == token)
    {
        retval =
            create_permission_with_username(
                perm, &details, permission_type, scanner);
        if (0 != retval)
        {
            goto error_exit;
        }
        goto done;
    }
    else if (FIDO_SCANNER_TOKEN_TYPE_GROUP == token)
    {
        retval =
            create_permission_with_group(
                perm, &details, permission_type, scanner);
        if (0 != retval)
        {
            goto error_exit;
        }
        goto done;
    }
    else if (FIDO_SCANNER_TOKEN_TYPE_EOF == token)
    {
        retval = FIDO_ERROR_UNEXPECTED_EOF;
        goto error_exit;
    }

    /* any other token is unexpected. */
    retval = FIDO_ERROR_UNEXPECTED_TOKEN;
    goto error_exit;

error_exit:
    *perm = NULL;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_permission, retval, perm, scanner);

    return retval;
}

/**
 * \brief Create a permission instance with the given username encoded in token
 * details.
 *
 * \param perm              Pointer to the permission pointer to set to the
 *                          created instance on success.
 * \param details           The token details from which the username is
 *                          extracted.
 * \param permission_type   The type of permission to create
 *                          \see fido_config_permission_type.
 * \param scanner           The scanner from which the username is extracted.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
static int create_permission_with_username(
    fido_config_permission** perm, const fido_token_details* details,
    int permission_type, fido_scanner* scanner)
{
    int retval;
    char username[1024];
    size_t name_len = (details->end_index - details->begin_index) + 2;
    const char* input = scanner->original_input;
    input += details->begin_index;

    /* bounds check on name length. */
    if (name_len > sizeof(username))
    {
        retval = FIDO_ERROR_BAD_LENGTH;
        goto done;
    }

    /* copy the username. */
    memcpy(username, input, name_len - 1);
    username[name_len - 1] = 0;

    /* create the permission instance. */
    retval =
        fido_config_permission_create(
            perm, username, FIDO_CONFIG_IDENTIFIER_TYPE_USERNAME,
            permission_type);
    goto done;

done:
    return retval;
}

/**
 * \brief Create a permission instance with the given group encoded in token
 * details.
 *
 * \param perm              Pointer to the permission pointer to set to the
 *                          created instance on success.
 * \param details           The token details from which the username is
 *                          extracted.
 * \param permission_type   The type of permission to create
 *                          \see fido_config_permission_type.
 * \param scanner           The scanner from which the username is extracted.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
static int create_permission_with_group(
    fido_config_permission** perm, const fido_token_details* details,
    int permission_type, fido_scanner* scanner)
{
    int retval;
    char username[1024];
    size_t name_len = (details->end_index - details->begin_index) + 2;
    const char* input = scanner->original_input;
    input += details->begin_index;

    /* THe name length should include the colon prefix for the group. */
    if (name_len <= 1)
    {
        retval = FIDO_ERROR_BAD_LENGTH;
        goto done;
    }

    /* skip the colon for the group. */
    input += 1;
    name_len -= 1;

    MODEL_ASSERT(name_len > 0);

    /* bounds check on name length. */
    if (name_len > sizeof(username))
    {
        retval = FIDO_ERROR_BAD_LENGTH;
        goto done;
    }

    /* copy the username. */
    memcpy(username, input, name_len - 1);
    username[name_len - 1] = 0;

    /* create the permission instance. */
    retval =
        fido_config_permission_create(
            perm, username, FIDO_CONFIG_IDENTIFIER_TYPE_GROUP,
            permission_type);
    goto done;

done:
    return retval;
}
