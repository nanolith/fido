/**
 * \file models/shadow/config/fido_config_parse_add_variable.c
 *
 * \brief Shadow implementation of \ref fido_config_parse_add_variable.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "config/parser_internal.h"

int nondet_retval();

int FN_DECL_MUST_CHECK
fido_config_parse_add_variable(
    fido_config_add_variable** var, fido_scanner* scanner)
{
    int retval, token;
    fido_token_details details;
    enum fido_error_code ec;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_add_variable, var, scanner);

    retval = nondet_retval();
    if (0 == retval)
    {
        retval = fido_config_add_variable_create_random(var);
        goto done;
    }
    else
    {
        ec = (enum fido_error_code)retval;
        MODEL_ASSUME(__CPROVER_enum_is_in_range(ec));
        goto done;
    }

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_add_variable, retval, var, scanner);

    return retval;
}
