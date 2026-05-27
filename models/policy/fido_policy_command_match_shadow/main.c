/**
 * \file models/policy/fido_policy_command_match_shadow/main.c
 *
 * \brief Model checks for shadow implementation of
 * \ref fido_policy_command_match.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>
#include <fido/options.h>
#include <fido/policy.h>

#include "../../helpers/config/config_helpers.h"
#include "../../helpers/options/options_helpers.h"

int nondet_retval();

int main(int argc, char* argv[])
{
    int retval;
    fido_options* opts;
    fido_config_command* cmd;
    fido_config_command_argument* arg;

    /* create options. */
    retval = fido_options_create_random(&opts);
    if (0 != retval)
    {
        goto done;
    }

    /* create the command. */
    retval = fido_config_command_create_random(&cmd);
    if (0 != retval)
    {
        goto cleanup_opts;
    }

    if (0 == nondet_retval())
    {
        retval = fido_config_command_argument_create_random(&arg);
        if (0 != retval)
        {
            goto cleanup_cmd;
        }
        fido_config_command_add_argument(cmd, arg);
    }

    if (0 == nondet_retval())
    {
        retval = fido_config_command_argument_create_random(&arg);
        if (0 != retval)
        {
            goto cleanup_cmd;
        }
        fido_config_command_add_argument(cmd, arg);
    }

    /* check to see if the command matches. */
    retval = fido_policy_command_match(cmd, opts);
    if (0 != retval)
    {
        goto cleanup_cmd;
    }

    retval = 0;
    goto cleanup_cmd;

cleanup_cmd:
    fido_config_command_release(cmd);

cleanup_opts:
    fido_options_release(opts);

done:
    return retval;
}
