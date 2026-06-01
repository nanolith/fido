/**
 * \file fido/policy_proc.h
 *
 * \brief Portable methods for interfacing with authentication frameworks.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/user.h>
#include <fido/function_contracts.h>
#include <fido/function_decl.h>
#include <fido/model_assert.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Provide an authentication challenge, read the response, and verify it
 * using either BSD Auth (OpenBSD) or PAM (FreeBSD / etc).
 *
 * \param user          The user for this challenge.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_auth_challenge(const fido_user* user);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_auth_challenge, const fido_user* user)
        /* the user is valid. */
        MODEL_ASSERT(property_fido_user_valid(user));
MODEL_CONTRACT_PRECONDITIONS_END(fido_auth_challenge)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
