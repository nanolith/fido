/**
 * \file models/shadow/policy/fido_policy_command_argument_match.c
 *
 * \brief Shadow impl of \ref fido_policy_command_argument_match.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy.h>

int nondet_retval();

/**
 * \brief Check to see if a given command argument matches the provided
 * argument.
 *
 * \param cmd_arg       The command argument to match.
 * \param arg           The argument for this match.
 *
 * \returns 0 on success (matched) and non-zero on failure (not matched).
 */
int FN_DECL_MUST_CHECK
fido_policy_command_argument_match(
    const fido_config_command_argument* cmd_arg, const char* arg)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_command_argument_match, cmd_arg, arg);

    int retval = nondet_retval();
    MODEL_ASSUME(0 == retval || FIDO_ERROR_POLICY_MATCH == retval);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_command_argument_match, retval, cmd_arg, arg);

    return retval;
}
