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

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
