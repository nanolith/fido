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
 *      - FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ROLE on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounteres bad
 *        input.
 *      - FIDO_SCANNER_TOKEN_TYPE_EOF if the scanner encounters an EOF
 *        condition.
 */
int FN_DECL_MUST_CHECK
fido_scanner_complete_token_keyword_role(
    fido_token_details* details, fido_scanner* scanner)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_scanner_complete_token_keyword_role, details, scanner);

    /* cache the start of the keyword. */
    details->begin_index = scanner->index;
    details->begin_col = scanner->col;
    details->begin_line = scanner->line;

    if ('o' != *(scanner->input + 1))
    {
        /* TODO - fall back to username. */
        goto bad_input;
    }
    fido_scanner_next_character(scanner);

    if ('l' != *(scanner->input + 1))
    {
        /* TODO - fall back to username. */
        goto bad_input;
    }
    fido_scanner_next_character(scanner + 1);

    if ('e' != *(scanner->input + 1))
    {
        /* TODO - fall back to username. */
        goto bad_input;
    }
    fido_scanner_next_character(scanner);

    if (isalnum(*(scanner->input + 1)))
    {
        /* TODO - fall back to username. */
        goto bad_input;
    }
    else
    {
        /* TODO - wrap this in end_input helper method. */
        retval = details->type = FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ROLE;
        details->end_index = scanner->index;
        details->end_col = scanner->col;
        details->end_line = scanner->line;

        fido_scanner_next_character(scanner);

        goto done;
    }

bad_input:
    retval = FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_complete_token_keyword_role, retval, details, scanner);

    return retval;
}
