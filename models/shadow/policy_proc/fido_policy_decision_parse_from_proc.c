/**
 * \file models/shadow/policy_proc/fido_policy_decision_parse_from_proc.c
 *
 * \brief Shadow implementation of \ref fido_policy_decision_parse_from_proc.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/error_codes.h>
#include <fido/policy_proc.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int FN_DECL_MUST_CHECK
fido_policy_decision_parse_from_proc(
    fido_policy_decision** dec, const fido_options* opts)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_decision_parse_from_proc, dec, opts);

    retval = fido_policy_decision_create_random(dec);

    if (0 != retval)
    {
        *dec = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_decision_parse_from_proc, retval, dec, opts);

    return retval;
}
