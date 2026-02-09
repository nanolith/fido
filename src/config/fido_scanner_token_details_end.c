/**
 * \file config/fido_scanner_token_details_end.c
 *
 * \brief End the token details for a given token type.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "scanner_internal.h"

/**
 * \brief End the current input token, populating token details.
 *
 * \param details           The details to populate with the end token data.
 * \param scanner           The scanner instance.
 * \param type              The token type.
 *
 * \returns the token type.
 */
int fido_scanner_token_details_end(
    fido_token_details* details, fido_scanner* scanner, int type)
{
    int retval = type;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_scanner_token_details_end, details, scanner, type);

    details->type = type;
    details->end_index = scanner->index;
    details->end_line = scanner->line;
    details->end_col = scanner->col;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_token_details_end, retval, details, scanner, type);

    return retval;
}
