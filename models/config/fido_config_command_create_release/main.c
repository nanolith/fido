/**
 * \file models/config/fido_config_command_create_release/main.c
 *
 * \brief Model checks for fido config command create / release.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

#include "config/parser_internal.h"

int main(int argc, char* argv[])
{
    int retval;
    fido_config_command* cmd = NULL;
    char binary[8];

    /* randomize binary, and ensure it is ASCIIZ. */
    __CPROVER_havoc_object(binary);
    binary[sizeof(binary)-1] = 0;

    /* create the command instance. */
    retval = fido_config_command_create(&cmd, binary);
    if (0 != retval)
    {
        return 1;
    }

    /* release the command instance. */
    fido_config_command_release(cmd);

    return 0;
}
