/**
 * \file models/config/fido_config_role_add_command/main.c
 *
 * \brief Model checks for \ref fido_config_role_add_command.
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
    fido_config_role* role = NULL;
    fido_config_command* cmd = NULL;

    /* create the role instance. */
    retval = fido_config_role_create_random(&role);
    if (0 != retval)
    {
        goto done;
    }

    /* create the command instance. */
    retval = fido_config_command_create_random(&cmd);
    if (0 != retval)
    {
        goto cleanup_role;
    }

    /* add the command to the role. */
    fido_config_role_add_command(role, cmd);

    /* release the role instance. */
    goto cleanup_role;

cleanup_role:
    fido_config_role_release(role);

done:
    return retval;
}
