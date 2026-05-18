/**
 * \file models/shadow/config/fido_config_parse_role_command_shadow_sink.c
 *
 * \brief Shadow implementation of \ref fido_config_parse_role_command that acts
 * as a sink.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "config/parser_internal.h"

int nondet_retval();

static int choose_retval()
{
    int retval = nondet_retval();
    enum fido_error_code ec = (enum fido_error_code)retval;

    MODEL_ASSUME(0 == retval || __CPROVER_enum_is_in_range(ec));

    return retval;
}

int FN_DECL_MUST_CHECK
fido_config_parse_role_command(
    fido_config_role* role, fido_scanner* scanner)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_role_command, role, scanner);

    retval = choose_retval();

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_role_command, retval, role, scanner);

    return retval;
}
