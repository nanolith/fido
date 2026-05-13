/**
 * \file models/helpers/config/fido_config_role_create_random.c
 *
 * \brief Non-deterministic role create helper.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "config_helpers.h"

int nondet_int();

/* return the input string or NULL. */
static const char* optional_string(const char* input)
{
    if (0 == nondet_int())
    {
        return input;
    }
    else
    {
        return NULL;
    }
}

int FN_DECL_MUST_CHECK
fido_config_role_create_random(fido_config_role** role)
{
    char name[8];
    char as_user[8];
    char as_group[8];

    /* randomize inputs, and ensure they are ASCIIZ. */
    __CPROVER_havoc_object(name);
    name[sizeof(name)-1] = 0;
    __CPROVER_havoc_object(as_user);
    as_user[sizeof(as_user)-1] = 0;
    __CPROVER_havoc_object(as_group);
    as_group[sizeof(as_group)-1] = 0;

    /* create the role instance. */
    return
        fido_config_role_create(
            role, name, optional_string(as_user), optional_string(as_group));
}
