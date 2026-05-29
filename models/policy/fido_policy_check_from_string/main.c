/**
 * \file models/policy/fido_policy_check_from_string/main.c
 *
 * \brief Model checks for \ref fido_policy_check_from_string.
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
bool nondet_bool();

bool choose_auth()
{
    return nondet_bool();
}

static char config[8];

const char* choose_config_str()
{
    __CPROVER_havoc_object(config);
    config[sizeof(config)-1]=0;

    return config;
}

int main(int argc, char* argv[])
{
    int retval;
    fido_options* opts;
    fido_user* user;
    fido_config_role* role;

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

    /* check to see if the policy matches. */
    retval =
        fido_policy_check_from_string(
            user, opts, choose_config_str(), choose_auth());
    if (0 != retval)
    {
        goto cleanup_user;
    }

    retval = 0;
    goto cleanup_user;

cleanup_user:
    fido_user_release(user);

cleanup_opts:
    fido_options_release(opts);

done:
    return retval;
}
