/**
 * \file models/shadow/policy/fido_policy_role_match.c
 *
 * \brief Shadow implementation of \ref fido_policy_role_match.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy.h>

int nondet_retval();

int FN_DECL_MUST_CHECK
fido_policy_role_match(
    const char** as_user, const char** as_group,
    const fido_config_add_variable** env_head, const fido_config_role* role,
    const fido_options* opts, const fido_user* user)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_role_match, as_user, as_group, env_head, role, opts, user);

    int retval = nondet_retval();
    MODEL_ASSUME(0 == retval || FIDO_ERROR_POLICY_MATCH == retval);

    if (0 == retval)
    {
        *as_user = role->as_user;
        *as_group = role->as_group;
        *env_head = role->variable_head;
    }
    else
    {
        *as_user = NULL;
        *as_group = NULL;
        *env_head = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_role_match, retval, as_user, as_group, env_head, role,
        opts, user);

    return retval;
}
