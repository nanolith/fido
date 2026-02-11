/**
 * \file config/fido_scanner_complete_token_keyword_cmd.c
 *
 * \brief Complete the scan of the cmd keyword.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>

#include "config/scanner_internal.h"

int nondet_status();

/**
 * \brief Attempt to complete a cmd keyword token.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_KEYWORD_CMD or
 *        FIDO_SCANNER_TOKEN_TYPE_USERNAME on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounters bad
 *        input.
 */
int FN_DECL_MUST_CHECK
fido_scanner_complete_token_keyword_cmd(
    fido_token_details* details, fido_scanner* scanner)
{
    int retval, peek;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_scanner_complete_token_keyword_cmd, details, scanner);

    if (0 == nondet_status())
    {
        peek = *(scanner->input + 1);
        if (0 == peek)
            goto hit_eof;
        fido_scanner_next_character(scanner);
    }
    else
    {
        goto bad_input;
    }

    if (0 == nondet_status())
    {
        retval =
            fido_scanner_token_details_end(
                details, scanner, FIDO_SCANNER_TOKEN_TYPE_KEYWORD_CMD);
        fido_scanner_next_character(scanner);
        goto done;
    }
    else
    {
        retval =
            fido_scanner_token_details_end(
                details, scanner, FIDO_SCANNER_TOKEN_TYPE_USERNAME);
        fido_scanner_next_character(scanner);
        goto done;
    }

hit_eof:
    retval = FIDO_SCANNER_TOKEN_TYPE_EOF;
    goto done;

bad_input:
    retval = FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_complete_token_keyword_cmd, retval, details, scanner);

    return retval;
}
