/**
 * \file config/fido_scanner_token_details_begin.c
 *
 * \brief Begin the token details for a given token type.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "scanner_internal.h"

/**
 * \brief Begin the input token, populating token details.
 *
 * \param details           The details to populate with the begin token data.
 * \param scanner           The scanner instance.
 *
 * \returns the token type.
 */
void fido_scanner_token_details_begin(
    fido_token_details* details, fido_scanner* scanner)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_scanner_token_details_begin, details, scanner);

    details->type = FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT;
    details->begin_index = details->end_index = scanner->index;
    details->begin_line = details->end_line = scanner->line;
    details->begin_col = details->end_col = scanner->col;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_token_details_begin, details, scanner);
}
