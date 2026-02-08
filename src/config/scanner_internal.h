/**
 * \file config/scanner_internal.h
 *
 * \brief Internal functions and types for the fido scanner.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/scanner.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/******************************************************************************/
/* Start of private methods.                                                  */
/******************************************************************************/

/**
 * \brief Attempt to complete a role keyword token.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ROLE on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounteres bad
 *        input.
 *      - FIDO_SCANNER_TOKEN_TYPE_EOF if the scanner encounters an EOF
 *        condition.
 */
int FN_DECL_MUST_CHECK
fido_scanner_complete_token_keyword_role(
    fido_token_details* details, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_complete_token_keyword_role, fido_token_details* details,
    fido_scanner* scanner)
        /* token details point to a valid region of memory. */
        MODEL_CHECK_OBJECT_RW(details, sizeof(*details));
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_complete_token_keyword_role)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
