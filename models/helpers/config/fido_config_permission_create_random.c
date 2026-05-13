/**
 * \file models/helpers/config/fido_config_permission_create_random.c
 *
 * \brief Non-deterministic permission create helper.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "config_helpers.h"

int nondet_int();

static int fido_config_permission_identifier_type()
{
    enum fido_config_identifier_type value =
        (enum fido_config_identifier_type)nondet_int();
    MODEL_ASSUME(__CPROVER_enum_is_in_range(value));

    return value;
}

static int fido_config_permission_permission_type()
{
    enum fido_config_permission_type value =
        (enum fido_config_permission_type)nondet_int();
    MODEL_ASSUME(__CPROVER_enum_is_in_range(value));

    return value;
}

int FN_DECL_MUST_CHECK
fido_config_permission_create_random(fido_config_permission** perm)
{
    char identifier[8];
    int identifier_type = fido_config_permission_identifier_type();
    int permission_type = fido_config_permission_permission_type();

    /* randomize identifier, and ensure it is ASCIIZ. */
    __CPROVER_havoc_object(identifier);
    identifier[sizeof(identifier)-1] = 0;

    /* create the permission instance. */
    return
        fido_config_permission_create(
            perm, identifier, identifier_type, permission_type);
}
