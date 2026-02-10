/**
 * \file config/fido_scanner_complete_token_simple.c
 *
 * \brief Complete the scan of a simple token.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>

#include "scanner_internal.h"

/**
 * \brief Complete a simple token of the given type.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 * \param type              The token type to scan.
 *
 * \returns a token from the scanner.
 *      - the given type.
 */
int FN_DECL_MUST_CHECK
fido_scanner_complete_token_simple(
    fido_token_details* details, fido_scanner* scanner, int type)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_scanner_complete_token_simple, details, scanner, type);

    retval = fido_scanner_token_details_end(details, scanner, type);

    fido_scanner_next_character(scanner);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_complete_token_simple, retval, details, scanner, type);

    return retval;
}
