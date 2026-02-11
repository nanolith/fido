/**
 * \file config/fido_scanner_read_token_string.c
 *
 * \brief Attempt to scan a string token.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>

#include "scanner_internal.h"

/**
 * \brief Attempt to read a string token.
 *
 * \note This function exists mainly for verification purposes. The function,
 * \ref fido_scanner_complete_token_string is used by the scanner
 * proper, and called by this function.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_STRING on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounters bad
 *        input.
 */
int FN_DECL_MUST_CHECK
fido_scanner_read_token_string(
    fido_token_details* details, fido_scanner* scanner)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_scanner_read_token_string, details, scanner);

    /* for this function, the token must begin with '"'. */
    if ('"' != *(scanner->input))
    {
        goto bad_input;
    }

    /* start the token. */
    fido_scanner_token_details_begin(details, scanner);

    /* attempt to complete this token. */
    retval = fido_scanner_complete_token_string(details, scanner);
    goto done;

bad_input:
    retval = FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_read_token_string, retval, details, scanner);

    return retval;
}
