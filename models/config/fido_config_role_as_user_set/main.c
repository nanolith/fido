/**
 * \file models/config/fido_config_role_as_user_set/main.c
 *
 * \brief Model checks for fido config role as user set.
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
    char as_user[10];

    /* randomize as_user. */
    __CPROVER_havoc_object(as_user);
    as_user[sizeof(as_user)-1] = 0;

    /* create the role instance. */
    retval = fido_config_role_create_random(&role);
    if (0 != retval)
    {
        goto done;
    }

    /* set as_user. */
    retval = fido_config_role_as_user_set(role, as_user);
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
