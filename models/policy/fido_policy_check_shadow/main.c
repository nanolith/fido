/**
 * \file models/policy/fido_policy_check_shadow/main.c
 *
 * \brief Model checks for shadow implementation of \ref fido_policy_check.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>
#include <fido/options.h>
#include <fido/policy.h>

#include "../../helpers/config/config_helpers.h"
#include "../../helpers/options/options_helpers.h"

int nondet_retval();

int main(int argc, char* argv[])
{
    int retval;
    fido_options* opts;
    fido_user* user;
    fido_config_role* role;
    fido_config* config;
    const char* as_user;
    const char* as_group;
    fido_config_add_variable* env_head;

    /* create options. */
    retval = fido_options_create_random(&opts);
    if (0 != retval)
    {
        goto done;
    }

    /* create user. */
    retval = fido_user_create_random(&user);
    if (0 != retval)
    {
        goto cleanup_opts;
    }

    /* create the config. */
    retval = fido_config_create_random(&config);
    if (0 != retval)
    {
        goto cleanup_user;
    }

    for (int i = 0; i < 2; ++i)
    {
        if (0 == nondet_retval())
        {
            retval = fido_config_role_create_random(&role);
            if (0 != retval)
            {
                goto cleanup_config;
            }
            fido_config_add_role(config, role);
        }
    }

    /* check to see if the policy matches. */
    retval =
        fido_policy_check(&as_user, &as_group, &env_head, config, opts, user);
    if (0 != retval)
    {
        goto cleanup_config;
    }

    retval = 0;
    goto cleanup_config;

cleanup_config:
    fido_config_release(config);

cleanup_user:
    fido_user_release(user);

cleanup_opts:
    fido_options_release(opts);

done:
    return retval;
}
