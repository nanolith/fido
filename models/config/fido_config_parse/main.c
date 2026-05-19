/**
 * \file models/config/fido_config_parse/main.c
 *
 * \brief Model checks for \ref fido_config_parse.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

#include "../../helpers/config/config_helpers.h"
#include "config/parser_internal.h"

extern int peek_tries;

int main(int argc, char* argv[])
{
    char input[3];
    int retval;
    fido_config* config = NULL;

    /* limit peek tries. */
    peek_tries = 2;

    /* randomize input, and ensure it is ASCIIZ. */
    __CPROVER_havoc_object(input);
    input[sizeof(input)-1] = 0;

    /* parse config. */
    retval = fido_config_parse(&config, input);
    if (0 != retval)
    {
        goto done;
    }

    /* clean up. */
    retval = 0;
    goto cleanup_config;

cleanup_config:
    fido_config_release(config);

done:
    return retval;
}
