/**
 * \file models/policy/fido_policy_permission_match/main.c
 *
 * \brief Model checks for \ref fido_policy_permission_match.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>
#include <fido/policy.h>

#include "../../helpers/config/config_helpers.h"
#include "../../helpers/user/user_helpers.h"

int main(int argc, char* argv[])
{
    int retval;
    fido_user* user;
    fido_config_permission* perm;
    char arg[8];

    /* create the user. */
    retval = fido_user_create_random(&user);
    if (0 != retval)
    {
        goto done;
    }

    /* create the permission. */
    retval = fido_config_permission_create_random(&perm);
    if (0 != retval)
    {
        goto cleanup_user;
    }

    /* check to see if the permission matches. */
    retval = fido_policy_permission_match(perm, user);
    if (0 != retval)
    {
        goto cleanup_perm;
    }

    retval = 0;
    goto cleanup_perm;

cleanup_perm:
    fido_config_permission_release(perm);

cleanup_user:
    fido_user_release(user);

done:
    return retval;
}
