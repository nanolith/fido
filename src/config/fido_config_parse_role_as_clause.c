/**
 * \file config/fido_config_parse_role_as_clause.c
 *
 * \brief Parse the as clause for a role from the input scanner.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Parse the as clause of a role.
 *
 * \param role          Role where this clause is saved on success.
 * \param scanner       The scanner to use to parse this as expression.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_parse_role_as_clause(
    fido_config_role* role, fido_scanner* scanner)
{
    int retval;
    char* str = NULL;
    int type;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_role_as_clause, role, scanner);

    /* attempt to parse the as clause. */
    retval = fido_config_parse_as(&str, &type, scanner);
    if (0 != retval)
    {
        goto done;
    }

    /* decode the type. */
    switch (type)
    {
        case FIDO_CONFIG_AS_TYPE_USER:
            if (NULL != role->as_user)
            {
                retval = FIDO_ERROR_DUPLICATE_AS_USERNAME;
                goto cleanup_str;
            }
            retval = fido_config_role_as_user_set(role, str);
            goto cleanup_str;

        case FIDO_CONFIG_AS_TYPE_GROUP:
            if (NULL != role->as_group)
            {
                retval = FIDO_ERROR_DUPLICATE_AS_GROUP;
                goto cleanup_str;
            }
            retval = fido_config_role_as_group_set(role, str);
            goto cleanup_str;

        default:
            retval = FIDO_ERROR_UNKNOWN_AS_TYPE;
            goto cleanup_str;
    }

cleanup_str:
    free(str);

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_role_as_clause, retval, role, scanner);

    return retval;
}
