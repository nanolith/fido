/**
 * \file config/fido_scanner_complete_token_keyword_role.c
 *
 * \brief Complete the scan of the role keyword.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>

#include "scanner_internal.h"

/**
 * \brief Attempt to complete a role keyword token.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ROLE or
 *        FIDO_SCANNER_TOKEN_TYPE_USERNAME on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounteres bad
 *        input.
 */
int FN_DECL_MUST_CHECK
fido_scanner_complete_token_keyword_role(
    fido_token_details* details, fido_scanner* scanner)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_scanner_complete_token_keyword_role, details, scanner);

    if ('o' != *(scanner->input + 1))
    {
        goto username_fallback;
    }
    fido_scanner_next_character(scanner);

    if ('l' != *(scanner->input + 1))
    {
        goto username_fallback;
    }
    fido_scanner_next_character(scanner);

    if ('e' != *(scanner->input + 1))
    {
        goto username_fallback;
    }
    fido_scanner_next_character(scanner);

    if (isalnum(*(scanner->input + 1)))
    {
        goto username_fallback;
    }
    else
    {
        retval =
            fido_scanner_token_details_end(
                details, scanner, FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ROLE);

        fido_scanner_next_character(scanner);

        goto done;
    }

username_fallback:
    retval = fido_scanner_complete_token_username(details, scanner);

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_complete_token_keyword_role, retval, details, scanner);

    return retval;
}
