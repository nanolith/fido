/**
 * \file models/config/fido_config_add_variable_create_release/main.c
 *
 * \brief Model checks for fido config add variable create / release.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

#include "config/parser_internal.h"

int main(int argc, char* argv[])
{
    int retval;
    fido_config_add_variable* var = NULL;
    char name[8];

    /* randomize name, and ensure it is ASCIIZ. */
    __CPROVER_havoc_object(name);
    name[sizeof(name)-1] = 0;

    /* create the variable instance. */
    retval = fido_config_add_variable_create(&var, name);
    if (0 != retval)
    {
        return 1;
    }

    /* release the variable instance. */
    fido_config_add_variable_release(var);

    return 0;
}
