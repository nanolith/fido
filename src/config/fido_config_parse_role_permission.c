/**
 * \file config/fido_config_parse_role_permission.c
 *
 * \brief Parse a permission for a role from the input scanner.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Parse a permission clause and add it to this role.
 *
 * \param role          Role where this permission clause is saved on success.
 * \param scanner       The scanner to use to parse this as expression.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_parse_role_permission(
    fido_config_role* role, fido_scanner* scanner)
{
    int retval;
    fido_config_permission* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_role_permission, role, scanner);

    /* parse a permission. */
    retval = fido_config_parse_permission(&tmp, scanner);
    if (0 != retval)
    {
        goto done;
    }

    /* add this permission to the role. */
    fido_config_role_add_permission(role, tmp);

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_role_permission, retval, role, scanner);

    return retval;
}
