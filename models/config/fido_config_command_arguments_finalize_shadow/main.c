/**
 * \file models/config/fido_config_command_arguments_finalize_shadow/main.c
 *
 * \brief Model checks for \ref fido_config_command_arguments_finalize_shadow.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

#include "../../helpers/config/config_helpers.h"
#include "config/parser_internal.h"

size_t nondet_size();

size_t arg_count()
{
    size_t x = nondet_size();
    if (x > 2)
        x = 2;

    return x;
}

int main(int argc, char* argv[])
{
    int retval;
    fido_config_command* cmd;
    fido_config_command_argument* arg[2] = { NULL, NULL };

    /* create command. */
    retval = fido_config_command_create_random(&cmd);
    if (0 != retval)
    {
        goto done;
    }

    /* create argument instance 0. */
    retval = fido_config_command_argument_create_random(&arg[0]);
    if (0 != retval)
    {
        goto cleanup_cmd;
    }

    /* create argument instance 1. */
    retval = fido_config_command_argument_create_random(&arg[1]);
    if (0 != retval)
    {
        goto cleanup_arguments;
    }

    /* add the arguments to the command. */
    size_t args = arg_count();
    for (size_t i = 0; i < args; ++i)
    {
        fido_config_command_add_argument(cmd, arg[i]);
        arg[i] = NULL;
    }

    /* finalize arguments. */
    fido_config_command_arguments_finalize(cmd);

    /* clean up. */
    goto cleanup_arguments;

cleanup_arguments:
    if (NULL != arg[0]) fido_config_command_argument_release(arg[0]);
    if (NULL != arg[1]) fido_config_command_argument_release(arg[1]);

cleanup_cmd:
    fido_config_command_release(cmd);

done:
    return retval;
}
