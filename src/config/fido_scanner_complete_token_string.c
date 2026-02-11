/**
 * \file config/fido_scanner_complete_token_string.c
 *
 * \brief Complete the scan of a string token.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>

#include "scanner_internal.h"

/* forward decls. */
static int handle_escape(fido_scanner* scanner);

/**
 * \brief Attempt to complete a string token.
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
fido_scanner_complete_token_string(
    fido_token_details* details, fido_scanner* scanner)
{
    int retval, peek;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_scanner_complete_token_string, details, scanner);

    peek = *(scanner->input + 1);

    /* iterate until the end of string. */
    while ('"' != peek)
    {
        switch (peek)
        {
            /* if the input terminates early, this is a bad input. */
            case 0:
                goto bad_input;

            /* handle escape sequences. */
            case '\\':
                retval = handle_escape(scanner);
                if (0 != retval)
                {
                    goto bad_input;
                }
                break;

            /* consume all other characters. */
            default:
                fido_scanner_next_character(scanner);
                break;
        }

        peek = *(scanner->input + 1);
    }

    fido_scanner_next_character(scanner);

    retval =
        fido_scanner_token_details_end(
            details, scanner, FIDO_SCANNER_TOKEN_TYPE_STRING);

    fido_scanner_next_character(scanner);

    goto done;

bad_input:
    retval = FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_complete_token_string, retval, details, scanner);

    return retval;
}

/**
 * \brief Handle escape sequences.
 *
 * \param details           Token details.
 * \param scanner           The scanner for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int handle_escape(fido_scanner* scanner)
{
    /* consume a character. */
    fido_scanner_next_character(scanner);

    int peek = *(scanner->input + 1);

    switch (peek)
    {
        case '*':
        case '%':
        case '\\':
        case '"':
        case 'f':
        case 'n':
        case 'r':
        case 't':
        case 'v':
            fido_scanner_next_character(scanner);
            return 0;

        default:
            return FIDO_ERROR_INVALID_INPUT;
    }
}
