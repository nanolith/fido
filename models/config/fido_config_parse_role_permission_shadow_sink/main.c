/**
 * \file models/config/fido_config_parse_role_permission_shadow_sink/main.c
 *
 * \brief Model checks for \ref fido_config_parse_role_permission_shadow_sink.
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
    fido_config_role* role = NULL;

    /* randomize input, and ensure it is ASCIIZ. */
    __CPROVER_havoc_object(input);
    input[sizeof(input)-1] = 0;

    /* create the scanner instance. */
    retval = fido_scanner_create(&scanner, input);
    if (0 != retval)
    {
        goto done;
    }

    /* create a random role instance. */
    retval = fido_config_role_create_random(&role);
    if (0 != retval)
    {
        goto cleanup_scanner;
    }

    /* parse a permission for a role. */
    retval = fido_config_parse_role_permission(role, scanner);
    if (0 != retval)
    {
        goto cleanup_role;
    }

    /* clean up. */
    retval = 0;
    goto cleanup_role;

cleanup_role:
    fido_config_role_release(role);

cleanup_scanner:
    fido_scanner_release(scanner);

done:
    return retval;
}
