/**
 * \file policy/fido_policy_check_from_descriptor.c
 *
 * \brief Shadow implementation of \ref fido_policy_check_from_descriptor.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy.h>

int nondet_retval();

int FN_DECL_MUST_CHECK
fido_policy_check_from_descriptor(
    const fido_user* user, const fido_options* opts, int fd,
    bool authoritative)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_check_from_descriptor, user, opts, fd, authoritative);

    int retval = nondet_retval();
    MODEL_ASSUME(0 == retval || FIDO_ERROR_POLICY_MATCH == retval);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_check_from_descriptor, retval, user, opts, fd,
        authoritative);

    return retval;
}
