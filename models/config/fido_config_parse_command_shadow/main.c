/**
 * \file models/config/fido_config_parse_command/main.c
 *
 * \brief Model checks for \ref fido_config_parse_command_shadow.
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
    fido_scanner* scanner = NULL;
    fido_config_command* cmd = NULL;

    /* randomize input, and ensure it is ASCIIZ. */
    __CPROVER_havoc_object(input);
    input[sizeof(input)-1] = 0;

    /* create the scanner instance. */
    retval = fido_scanner_create(&scanner, input);
    if (0 != retval)
    {
        goto done;
    }

    /* parse command. */
    retval = fido_config_parse_command(&cmd, scanner);
    if (0 != retval)
    {
        goto cleanup_scanner;
    }

    /* clean up. */
    retval = 0;
    goto cleanup_cmd;

cleanup_cmd:
    fido_config_command_release(cmd);

cleanup_scanner:
    fido_scanner_release(scanner);

done:
    return retval;
}
