/**
 * \file models/shadow/config/fido_config_parse_command.c
 *
 * \brief This shadow form of \ref fido_config_parse_command.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>
#include <fido/scanner.h>

#include "config/scanner_internal.h"

int nondet_retval();

int FN_DECL_MUST_CHECK
fido_config_parse_command(
    fido_config_command** cmd, fido_scanner* scanner)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_command, cmd, scanner);

    retval = nondet_retval();
    if (0 != retval)
    {
        enum fido_error_code ec = (enum fido_error_code)retval;
        MODEL_ASSUME(__CPROVER_enum_is_in_range(ec));
        goto done;
    }

    retval = fido_config_command_create_random(cmd);
    if (0 == retval)
    {
        (*cmd)->arguments_finalized = true;
    }
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_command, retval, cmd, scanner);

    return retval;
}
