/**
 * \file policy/fido_policy_permission_match.c
 *
 * \brief Shadow implementation of \ref fido_policy_permission_match.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/error_codes.h>
#include <fido/policy.h>

int nondet_retval();

int FN_DECL_MUST_CHECK
fido_policy_permission_match(
    const fido_config_permission* perm, const fido_user* user)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_permission_match, perm, user);

    int retval = nondet_retval();
    MODEL_ASSUME(0 == retval || FIDO_ERROR_POLICY_MATCH == retval);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_permission_match, retval, perm, user);

    return retval;
}
