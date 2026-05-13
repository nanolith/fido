/**
 * \file models/helpers/config/fido_config_command_argument_create_random.c
 *
 * \brief Non-deterministic command_argument create helper.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "config_helpers.h"

int nondet_int();

static int fido_config_command_argument_argument_type()
{
    enum fido_config_command_argument_type value =
        (enum fido_config_command_argument_type)nondet_int();
    MODEL_ASSUME(__CPROVER_enum_is_in_range(value));

    return value;
}

int FN_DECL_MUST_CHECK
fido_config_command_argument_create_random(fido_config_command_argument** arg)
{
    char argument_match[8];
    int argument_type = fido_config_command_argument_argument_type();

    /* randomize argument match, and ensure it is ASCIIZ. */
    __CPROVER_havoc_object(argument_match);
    argument_match[sizeof(argument_match)-1] = 0;

    /* create the command argument instance. */
    return
        fido_config_command_argument_create(arg, argument_type, argument_match);
}
