/**
 * \file config/fido_scanner_next_character.c
 *
 * \brief Move to the next character in the scanner.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "scanner_internal.h"

/**
 * \brief Skip to the next character.
 *
 * \param scanner           The scanner instance for this operation.
 */
void fido_scanner_next_character(fido_scanner* scanner)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_scanner_next_character, scanner);

    if ('\n' == *(scanner->input))
    {
        scanner->col = 1;
        scanner->line += 1;
    }
    else
    {
        scanner->col += 1;
    }

    scanner->input += 1;
    scanner->index += 1;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_scanner_next_character, scanner);
}
