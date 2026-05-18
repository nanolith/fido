/**
 * \file config/fido_config_parse_role_command.c
 *
 * \brief Parse a command for a role from the input scanner.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Parse a command and add it to this role.
 *
 * \param role          Role where this command is saved on success.
 * \param scanner       The scanner to use to parse this as expression.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_parse_role_command(
    fido_config_role* role, fido_scanner* scanner)
{
    int retval;
    fido_config_command* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_role_command, role, scanner);


    /* parse a command. */
    retval = fido_config_parse_command(&tmp, scanner);
    if (0 != retval)
    {
        goto done;
    }

    /* add this command to the role. */
    fido_config_role_add_command(role, tmp);

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_role_command, retval, role, scanner);

    return retval;
}
