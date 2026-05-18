/**
 * \file config/fido_config_parse_role_as_clause_shadow_sink.c
 *
 * \brief Shadow implementation of \ref fido_config_parse_role_as_clause.
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
    MODEL_ASSUME(retval == 0 || __CPROVER_enum_is_in_range(ec));

    return retval;
}

int FN_DECL_MUST_CHECK
fido_config_parse_role_as_clause(
    fido_config_role* role, fido_scanner* scanner)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_role_as_clause, role, scanner);

    retval = choose_retval();

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_role_as_clause, retval, role, scanner);

    return retval;
}
