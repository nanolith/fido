/**
 * \file models/config/fido_config_role_as_group_set/main.c
 *
 * \brief Model checks for fido config role as group set.
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
    fido_config_role* role;
    char as_group[10];

    /* randomize as_group. */
    __CPROVER_havoc_object(as_group);
    as_group[sizeof(as_group)-1] = 0;

    /* create the role instance. */
    retval = fido_config_role_create_random(&role);
    if (0 != retval)
    {
        goto done;
    }

    /* set as_group. */
    retval = fido_config_role_as_group_set(role, as_group);
    if (0 != retval)
    {
        goto cleanup_role;
    }

    goto cleanup_role;

cleanup_role:
    /* release the role instance. */
    fido_config_role_release(role);

done:
    return retval;
}
