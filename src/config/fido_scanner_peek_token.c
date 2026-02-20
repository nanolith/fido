/**
 * \file config/fido_scanner_peek_token.c
 *
 * \brief Peek a token from the scanner.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>
#include <string.h>

#include "scanner_internal.h"

/**
 * \brief Peek a token from the scanner instance, populating the provided token
 * structure with details.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_EOF at the end of input.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounters bad
 *        input.
 *      - a value belonging to the \ref fido_scanner_token_type enumeration.
 */
int FN_DECL_MUST_CHECK
fido_scanner_peek_token(
    fido_token_details* details, fido_scanner* scanner)
{
    int retval;
    fido_scanner backup;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_scanner_peek_token, details, scanner);

    /* Back up scanner state. */
    memcpy(&backup, scanner, sizeof(backup));

    /* read the next token. */
    retval = fido_scanner_read_token(details, scanner);

    /* Restore scanner state. */
    memcpy(scanner, &backup, sizeof(backup));

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_peek_token, retval, details, scanner);

    return retval;
}
