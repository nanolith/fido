/**
 * \file models/helpers/config/fido_config_add_variable_create_random.c
 *
 * \brief Non-deterministic add_variable create helper.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "config_helpers.h"

int FN_DECL_MUST_CHECK
fido_config_add_variable_create_random(fido_config_add_variable** var)
{
    char name[8];

    /* randomize name, and ensure it is ASCIIZ. */
    __CPROVER_havoc_object(name);
    name[sizeof(name)-1] = 0;

    /* create the variable instance. */
    return fido_config_add_variable_create(var, name);
}
