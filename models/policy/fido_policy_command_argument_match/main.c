/**
 * \file models/policy/fido_policy_command_argument_match/main.c
 *
 * \brief Model checks for \ref fido_policy_command_argument_match.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>
#include <fido/policy.h>

#include "../../helpers/user/user_helpers.h"

int main(int argc, char* argv[])
{
    int retval;
    fido_config_command_argument* cmd_arg;
    char arg[8];

    __CPROVER_havoc_object(arg);
    arg[sizeof(arg)-1] = 0;

    /* create the command argument instance. */
    retval = fido_config_command_argument_create_random(&cmd_arg);
    if (0 != retval)
    {
        goto done;
    }

    /* check to see if the argument matches. */
    retval = fido_policy_command_argument_match(cmd_arg, arg);
    if (0 != retval)
    {
        goto cleanup_cmd_arg;
    }

    retval = 0;
    goto cleanup_cmd_arg;

cleanup_cmd_arg:
    /* release the command argument instance. */
    fido_config_command_argument_release(cmd_arg);

done:
    return retval;
}
