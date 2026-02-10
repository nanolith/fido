/**
 * \file config/fido_scanner_complete_token_identifier.c
 *
 * \brief Complete the scan of an identifier.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>

#include "scanner_internal.h"

/**
 * \brief Attempt to complete an identifier token.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 * \param type              The token type to scan.
 * \param read_start        Flag to indicate whether we should read the start of
 *                          the identifier.
 *
 * \returns a token from the scanner.
 *      - the given type on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounters bad
 *        input.
 */
int FN_DECL_MUST_CHECK
fido_scanner_complete_token_identifier(
    fido_token_details* details, fido_scanner* scanner, int type,
    bool read_start)
{
    int retval, peek;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_scanner_complete_token_identifier, details, scanner, type,
        read_start);

    peek = *(scanner->input + 1);

    if (read_start)
    {
        if (!isalpha(peek) && '_' != peek)
        {
            goto bad_input;
        }
    }

    while (isalnum(peek) || '_' == peek)
    {
        fido_scanner_next_character(scanner);
        peek = *(scanner->input + 1);
    }

    retval = fido_scanner_token_details_end(details, scanner, type);

    fido_scanner_next_character(scanner);

    goto done;

bad_input:
    retval = FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_complete_token_identifier, retval, details, scanner, type,
        read_start);

    return retval;
}
