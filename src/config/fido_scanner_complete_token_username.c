/**
 * \file config/fido_scanner_complete_token_username.c
 *
 * \brief Complete the scan of a username.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>

#include "scanner_internal.h"

/**
 * \brief Attempt to complete a username token.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_USERNAME on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounteres bad
 *        input.
 */
int FN_DECL_MUST_CHECK
fido_scanner_complete_token_username(
    fido_token_details* details, fido_scanner* scanner)
{
    int retval, peek;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_scanner_complete_token_username, details, scanner);

    peek = *(scanner->input + 1);

    while (isalnum(peek) || '_' == peek)
    {
        fido_scanner_next_character(scanner);
        peek = *(scanner->input + 1);
    }

    retval =
        fido_scanner_token_details_end(
            details, scanner, FIDO_SCANNER_TOKEN_TYPE_USERNAME);

    fido_scanner_next_character(scanner);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_complete_token_username, retval, details, scanner);

    return retval;
}
