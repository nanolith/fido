/**
 * \file models/shadow/policy_proc/fido_policy_decision_parse_from_descriptor.c
 *
 * \brief Shadow implementation of fido_policy_decision_parse_from_descriptor.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <errno.h>
#include <fido/policy_proc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../../helpers/policy_proc/policy_proc_helpers.h"

int nondet_retval();

int FN_DECL_MUST_CHECK
fido_policy_decision_parse_from_descriptor(fido_policy_decision** dec, int fd)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_decision_parse_from_descriptor, dec, fd);

    retval = nondet_retval();
    enum fido_error_code ec = (enum fido_error_code)retval;
    MODEL_ASSUME(0 == retval || __CPROVER_enum_is_in_range(ec));

    if (0 != retval)
    {
        goto done;
    }

    retval = fido_policy_decision_create_random(dec);
    if (0 != retval)
    {
        /* trim this branch from the decision tree. */
        MODEL_ASSUME(0);
    }

    /* success. */
    retval = 0;
    goto done;

done:
    if (0 != retval)
    {
        *dec = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_decision_parse_from_descriptor, retval, dec, fd);

    return retval;
}
