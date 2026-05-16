/**
 * \file models/config/fido_config_parse_command_arguments/main.c
 *
 * \brief Model checks for \ref fido_config_parse_command_arguments.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

#include "../../helpers/config/config_helpers.h"
#include "config/parser_internal.h"

int main(int argc, char* argv[])
{
    char input[10];
    int retval;
    fido_config_command* cmd = NULL;

    /* randomize input, and ensure it is ASCIIZ. */
    __CPROVER_havoc_object(input);
    input[sizeof(input)-1] = 0;

    /* create the command instance. */
    retval = fido_config_command_create_random(&cmd);
    if (0 != retval)
    {
        goto done;
    }

    /* parse arguments. */
    retval = fido_config_parse_command_arguments(cmd, input);
    if (0 != retval)
    {
        goto cleanup_cmd;
    }

    /* clean up. */
    retval = 0;
    goto cleanup_cmd;

cleanup_cmd:
    fido_config_command_release(cmd);

done:
    return retval;
}
