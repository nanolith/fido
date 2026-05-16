/**
 * \file models/shadow/config/fido_config_parse_command_arguments.c
 *
 * \brief Shadow implementation of \ref fido_config_parse_command_arguments.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "config/parser_internal.h"

int nondet_retval();

int FN_DECL_MUST_CHECK
fido_config_parse_command_arguments(
    fido_config_command* cmd, char* str)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_command_arguments, cmd, str);

    retval = nondet_retval();
    enum fido_error_code ec = (enum fido_error_code)retval;
    MODEL_ASSUME(0 == retval || __CPROVER_enum_is_in_range(ec));

    if (0 == retval)
    {
        cmd->arguments_finalized = true;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_command_arguments, retval, cmd, str);

    return retval;

}
