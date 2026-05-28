/**
 * \file policy/fido_policy_check.c
 *
 * \brief Shadow implementation of \ref fido_policy_check.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy.h>

int nondet_retval();

int FN_DECL_MUST_CHECK
fido_policy_check(
    const char** as_user, const char** as_group,
    const fido_config_add_variable** env_head, const fido_config* config,
    const fido_options* opts, const fido_user* user)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_check, as_user, as_group, env_head, config, opts, user);
    char au[8];

    int retval = nondet_retval();
    MODEL_ASSUME(0 == retval || FIDO_ERROR_POLICY_MATCH == retval);

    if (0 != retval)
    {
        *as_user = NULL;
        *as_group = NULL;
        *env_head = NULL;
    }
    else
    {
        __CPROVER_havoc_object(au);
        au[sizeof(au)-1] = 0;
        *as_user = au;
        *as_group = au;
        *env_head = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_check, retval, as_user, as_group, env_head, config, opts,
        user);

    return retval;
}
