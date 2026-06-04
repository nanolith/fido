/**
 * \file fido/path.h
 *
 * \brief Methods for parsing and searching the path.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/error_codes.h>
#include <fido/function_contracts.h>
#include <fido/function_decl.h>
#include <fido/model_assert.h>
#include <stdbool.h>
#include <stddef.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Resolve a command given the following path; copy the current command
 * if the provided path includes a slash in it already.
 *
 * \param resolved      On success, this holds a copy of the resolved path.
 * \param input_path    The input path to consider.
 * \param command       The command to resolve.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_path_resolve(char** resolved, const char* input_path, const char* command);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_path_resolve, char** resolved, const char* input_path,
    const char* command)
        /* the resolved pointer is valid. */
        MODEL_CHECK_OBJECT_RW(resolved, sizeof(*resolved));
        /* input_path is not NULL. */
        MODEL_ASSERT(NULL != input_path);
        /* command is not NULL. */
        MODEL_ASSERT(NULL != command);
MODEL_CONTRACT_PRECONDITIONS_END(fido_path_resolve)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_path_resolve, int retval, char** resolved, const char* input_path,
    const char* command)
        /* on success... */
        if (0 == retval)
        {
            /* resolved is set to the resolved path. */
            MODEL_ASSERT(NULL != *resolved);
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* resolved is set to NULL. */
            MODEL_ASSERT(NULL == *resolved);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_path_resolve)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
