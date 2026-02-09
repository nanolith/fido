/**
 * \file config/fido_scanner_read_token_keyword_deny.c
 *
 * \brief Attempt to scan a deny keyword, falling back to username if 'r'
 * matches, and failing if it does not.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>

#include "scanner_internal.h"

/**
 * \brief Attempt to read a deny keyword token.
 *
 * \note This function exists mainly for verification purposes. The function,
 * \ref fido_scanner_complete_token_keyword_deny is used by the scanner
 * proper, and called by this function.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_KEYWORD_DENY or
 *        FIDO_SCANNER_TOKEN_TYPE_USERNAME on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounteres bad
 *        input.
 */
int FN_DECL_MUST_CHECK
fido_scanner_read_token_keyword_deny(
    fido_token_details* details, fido_scanner* scanner)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_scanner_read_token_keyword_deny, details, scanner);

    /* for this function, the token must begin with 'd'. */
    if ('d' != *(scanner->input))
    {
        goto bad_input;
    }

    /* start the token. */
    fido_scanner_token_details_begin(details, scanner);

    /* attempt to complete this token. */
    retval = fido_scanner_complete_token_keyword_deny(details, scanner);
    goto done;

bad_input:
    retval = FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_read_token_keyword_deny, retval, details, scanner);

    return retval;
}
