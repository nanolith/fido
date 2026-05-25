/**
 * \file models/config/fido_config_roles_finalize_shadow/main.c
 *
 * \brief Model checks for \ref fido_config_roles_finalize_shadow.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

#include "../../helpers/config/config_helpers.h"
#include "config/parser_internal.h"

size_t nondet_size();

size_t role_count()
{
    size_t x = nondet_size();
    if (x > 2)
        x = 2;

    return x;
}

int main(int argc, char* argv[])
{
    int retval;
    fido_config* config;
    fido_config_role* role[2] = { NULL, NULL };

    /* create config. */
    retval = fido_config_create(&config);
    if (0 != retval)
    {
        goto done;
    }

    /* create role instance 0. */
    retval = fido_config_role_create(&role[0], "a", "a", "a");
    if (0 != retval)
    {
        goto cleanup_config;
    }

    /* create role instance 1. */
    retval = fido_config_role_create(&role[1], "a", "a", "a");
    if (0 != retval)
    {
        goto cleanup_roles;
    }

    /* add the roles to the config. */
    size_t roles = role_count();
    for (size_t i = 0; i < roles; ++i)
    {
        fido_config_add_role(config, role[i]);
        role[i] = NULL;
    }

    /* finalize roles. */
    fido_config_roles_finalize(config);

    /* clean up. */
    goto cleanup_roles;

cleanup_roles:
    if (NULL != role[0]) fido_config_role_release(role[0]);
    if (NULL != role[1]) fido_config_role_release(role[1]);

cleanup_config:
    fido_config_release(config);

done:
    return retval;
}
