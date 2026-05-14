/**
 * \file models/config/fido_config_command_add_argument/main.c
 *
 * \brief Model checks for \ref fido_config_command_add_argument.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

#include "../../helpers/config/config_helpers.h"
#include "config/parser_internal.h"

int main(int argc, char* argv[])
{
    int retval;
    fido_config_command* cmd = NULL;
    fido_config_command_argument* arg = NULL;

    /* create the command instance. */
    retval = fido_config_command_create_random(&cmd);
    if (0 != retval)
    {
        goto done;
    }

    /* create the argument instance. */
    retval = fido_config_command_argument_create_random(&arg);
    if (0 != retval)
    {
        goto cleanup_cmd;
    }

    /* add the argument to the command. */
    fido_config_command_add_argument(cmd, arg);

    /* release the command instance. */
    goto cleanup_cmd;

cleanup_cmd:
    fido_config_command_release(cmd);

done:
    return retval;
}
