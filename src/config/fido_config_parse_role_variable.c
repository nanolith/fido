/**
 * \file config/fido_config_parse_role_variable.c
 *
 * \brief Parse an environment variable for a role from the input scanner.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Parse an environment variable clause and add it to this role.
 *
 * \param role          Role where this variable clause is saved on success.
 * \param scanner       The scanner to use to parse this as expression.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_parse_role_variable(
    fido_config_role* role, fido_scanner* scanner)
{
    int retval;
    fido_config_add_variable* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_role_variable, role, scanner);

    /* parse an add variable. */
    retval = fido_config_parse_add_variable(&tmp, scanner);
    if (0 != retval)
    {
        goto done;
    }

    /* add this variable to the role. */
    fido_config_role_add_variable(role, tmp);

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_role_variable, retval, role, scanner);

    return retval;
}
