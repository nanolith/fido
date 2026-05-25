/**
 * \file models/config/fido_config_command_create_release/main.c
 *
 * \brief Model checks for fido config command create / release.
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
    fido_config_command* cmd;

    /* create random command instance. */
    retval = fido_config_command_create_random(&cmd);
    if (0 != retval)
    {
        return 1;
    }

    /* release the command instance. */
    fido_config_command_release(cmd);

    return 0;
}
