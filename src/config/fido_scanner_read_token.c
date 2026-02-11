/**
 * \file config/fido_scanner_read_token.c
 *
 * \brief Read a token from the scanner.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>

#include "scanner_internal.h"

/**
 * \brief Read a token from the scanner instance, populating the provided token
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
fido_scanner_read_token(
    fido_token_details* details, fido_scanner* scanner)
{
    int retval, ch;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_scanner_read_token, details, scanner);

    /* read the first non-whitespace character. */
    ch = fido_scanner_skip_whitespace(scanner);
    fido_scanner_token_details_begin(details, scanner);

    switch (ch)
    {
        case 0:
            retval =
                fido_scanner_token_details_end(
                    details, scanner, FIDO_SCANNER_TOKEN_TYPE_EOF);
            goto done;

        case '"':
            retval = fido_scanner_complete_token_string(details, scanner);
            goto done;

        case '{':
            retval =
                fido_scanner_token_details_end(
                    details, scanner, FIDO_SCANNER_TOKEN_TYPE_OPEN_BRACE);
            goto consume_input;

        case '}':
            retval =
                fido_scanner_token_details_end(
                    details, scanner, FIDO_SCANNER_TOKEN_TYPE_CLOSE_BRACE);
            goto consume_input;

        case '+':
            retval =
                fido_scanner_complete_token_identifier(
                    details, scanner, FIDO_SCANNER_TOKEN_TYPE_ADD_VARIABLE,
                    true);
            goto done;

        case ':':
            retval =
                fido_scanner_complete_token_identifier(
                    details, scanner, FIDO_SCANNER_TOKEN_TYPE_GROUP, true);
            goto done;

        case 'a':
            retval = fido_scanner_complete_token_keyword_as(details, scanner);
            goto done;

        case 'c':
            retval = fido_scanner_complete_token_keyword_cmd(details, scanner);
            goto done;

        case 'd':
            retval = fido_scanner_complete_token_keyword_deny(details, scanner);
            goto done;

        case 'e':
            retval = fido_scanner_complete_token_keyword_env(details, scanner);
            goto done;

        case 'p':
            retval =
                fido_scanner_complete_token_keyword_permit(details, scanner);
            goto done;

        case 'r':
            retval = fido_scanner_complete_token_keyword_role(details, scanner);
            goto done;
    }

    /* is this an alpha or underscore? */
    if (isalpha(ch) || '_' == ch)
    {
        retval =
            fido_scanner_complete_token_identifier(
                details, scanner, FIDO_SCANNER_TOKEN_TYPE_USERNAME, false);
        goto done;
    }

    /* in all other cases, this is bad input. */
    retval =
        fido_scanner_token_details_end(
            details, scanner, FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT);
    goto done;

consume_input:
    fido_scanner_next_character(scanner);

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_read_token, retval, details, scanner);

    return retval;
}
