/**
 * \file fido/sandbox.h
 *
 * \brief Sandbox related methods.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/function_contracts.h>
#include <fido/function_decl.h>
#include <fido/model_assert.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Enter sandbox mode via capsicum on FreeBSD or pledge / unveil on
 * OpenBSD.
 *
 * \returns 0 on success and non-zero on failure.
 */
int FN_DECL_MUST_CHECK sandbox_enter(void);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(sandbox_enter, void)
MODEL_CONTRACT_PRECONDITIONS_END(sandbox_enter)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(sandbox_enter, int retval)
        /* this is a defined error code. */
        enum fido_error_code error = (enum fido_error_code)retval;
        MODEL_ASSERT(0 == retval || __CPROVER_enum_is_in_range(error));
MODEL_CONTRACT_POSTCONDITIONS_END(sandbox_enter)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
