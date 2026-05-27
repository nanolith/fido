/**
 * \file models/shadow/policy/fido_policy_command_match.c
 *
 * \brief Shadow implementation of \ref fido_policy_command_match.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy.h>
#include <string.h>

int nondet_retval();

int FN_DECL_MUST_CHECK
fido_policy_command_match(
    const fido_config_command* cmd, const fido_options* opts)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_policy_command_match, cmd, opts);

    int retval = nondet_retval();
    MODEL_ASSUME(0 == retval || FIDO_ERROR_POLICY_MATCH == retval);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_command_match, retval, cmd, opts);

    return retval;
}
