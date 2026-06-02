/**
 * \file fido/exec.h
 *
 * \brief Execute a binary as the set user, using the given options.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/error_codes.h>
#include <fido/function_contracts.h>
#include <fido/function_decl.h>
#include <fido/model_assert.h>
#include <fido/options.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Execute a binary using the given options.
 *
 * \param opts          The options to use for this binary.
 *
 * \returns 0 on success and non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_exec(const fido_options* opts);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_exec, const fido_options* opts)
        /* opts is valid. */
        MODEL_ASSERT(property_fido_options_valid(opts));
MODEL_CONTRACT_PRECONDITIONS_END(fido_exec)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_exec, int retval, const fido_options* opts)
        /* This function does not return on failure. */
        MODEL_ASSERT(0 != retval);

        /* this is a defined error code. */
        enum fido_error_code error = (enum fido_error_code)retval;
        MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
MODEL_CONTRACT_POSTCONDITIONS_END(fido_exec)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
