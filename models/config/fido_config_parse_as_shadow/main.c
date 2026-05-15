/**
 * \file models/config/fido_config_parse_as_shadow/main.c
 *
 * \brief Model checks for \ref fido_config_parse_as_shadow.
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
    char input[10];
    char* str = NULL;
    int type = -1;
    fido_scanner* scanner = NULL;

    /* randomize input, and ensure it is ASCIIZ. */
    __CPROVER_havoc_object(input);
    input[sizeof(input)-1] = 0;

    /* create the scanner instance. */
    retval = fido_scanner_create(&scanner, input);
    if (0 != retval)
    {
        goto done;
    }

    /* parse an as clause. */
    retval = fido_config_parse_as(&str, &type, scanner);
    if (0 != retval)
    {
        goto cleanup_scanner;
    }

    /* clean up. */
    goto cleanup_str;

cleanup_str:
    free(str);

cleanup_scanner:
    fido_scanner_release(scanner);

done:
    return retval;
}
