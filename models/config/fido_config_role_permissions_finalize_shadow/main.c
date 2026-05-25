/**
 * \file models/config/fido_config_role_permissionss_finalize_shadow/main.c
 *
 * \brief Model checks for \ref fido_config_role_permissions_finalize_shadow.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

#include "../../helpers/config/config_helpers.h"
#include "config/parser_internal.h"

size_t nondet_size();

size_t perm_count()
{
    size_t x = nondet_size();
    if (x > 2)
        x = 2;

    return x;
}

int main(int argc, char* argv[])
{
    int retval;
    fido_config_role* role;
    fido_config_permission* perm[2] = { NULL, NULL };

    /* create role. */
    retval = fido_config_role_create_random(&role);
    if (0 != retval)
    {
        goto done;
    }

    /* create permission instance 0. */
    retval = fido_config_permission_create_random(&perm[0]);
    if (0 != retval)
    {
        goto cleanup_role;
    }

    /* create permission instance 1. */
    retval = fido_config_permission_create_random(&perm[1]);
    if (0 != retval)
    {
        goto cleanup_permissions;
    }

    /* add the permissions to the role. */
    size_t permissions = perm_count();
    for (size_t i = 0; i < permissions; ++i)
    {
        fido_config_role_add_permission(role, perm[i]);
        perm[i] = NULL;
    }

    /* finalize permissions. */
    fido_config_role_permissions_finalize(role);

    /* clean up. */
    goto cleanup_permissions;

cleanup_permissions:
    if (NULL != perm[0]) fido_config_permission_release(perm[0]);
    if (NULL != perm[1]) fido_config_permission_release(perm[1]);

cleanup_role:
    fido_config_role_release(role);

done:
    return retval;
}
