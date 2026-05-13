/**
 * \file models/config/fido_config_command_argument_create_release/main.c
 *
 * \brief Model checks for fido config command argument create / release.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

#include "config/parser_internal.h"

int nondet_int();

static int fido_config_command_argument_argument_type()
{
    enum fido_config_command_argument_type value =
        (enum fido_config_command_argument_type)nondet_int();
    MODEL_ASSUME(__CPROVER_enum_is_in_range(value));

    return value;
}

int main(int argc, char* argv[])
{
    int retval;
    fido_config_command_argument* arg = NULL;
    char argument_match[8];
    int argument_type = fido_config_command_argument_argument_type();

    /* randomize argument match, and ensure it is ASCIIZ. */
    __CPROVER_havoc_object(argument_match);
    argument_match[sizeof(argument_match)-1] = 0;

    /* create the command argument instance. */
    retval =
        fido_config_command_argument_create(
            &arg, argument_type, argument_match);
    if (0 != retval)
    {
        return 1;
    }

    /* release the command argument instance. */
    fido_config_command_argument_release(arg);

    return 0;
}
