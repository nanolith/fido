/**
 * \file config/fido_scanner_skip_whitespace.c
 *
 * \brief Skip whitespace to get to the start of the next token.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>

#include "scanner_internal.h"

/**
 * \brief Skip whitespace to get the start of the next token.
 *
 * \param scanner       The scanner instance for this operation.
 *
 * \returns the start of the next token.
 */
int fido_scanner_skip_whitespace(fido_scanner* scanner)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_scanner_skip_whitespace, scanner);

    while (*(scanner->input) != 0 && isspace(*(scanner->input)))
    {
        fido_scanner_next_character(scanner);
    }

    retval = (unsigned char)*(scanner->input);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_skip_whitespace, retval, scanner);

    return retval;
}
