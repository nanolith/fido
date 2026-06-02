/**
 * \file fido/user_context.h
 *
 * \brief Data structures and methods relating to setting a user context.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/error_codes.h>
#include <fido/function_contracts.h>
#include <fido/function_decl.h>
#include <fido/model_assert.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Look up the password entry for a given user and group, and set the
 * group and user context.
 *
 * \note For now, we don't respect group override. TODO we will need to visit
 * this.
 *
 * \param username      The username for this operation.
 * \param groupname     The groupname for this operation.
 *
 * \returns 0 on success and non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_set_user_context(const char* username, const char* groupname);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_set_user_context, const char* username, const char* groupname)
        /* username and groupname are not NULL. */
        MODEL_ASSERT(NULL != username);
        MODEL_ASSERT(NULL != groupname);
MODEL_CONTRACT_PRECONDITIONS_END(fido_set_user_context)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
