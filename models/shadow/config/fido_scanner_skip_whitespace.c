/**
 * \file models/shadow/config/fido_scanner_skip_whitespace.c
 *
 * \brief fido_scanner_skip_whitespace shadow impl.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>

#include "config/scanner_internal.h"

int nondet_status();

int fido_scanner_skip_whitespace(fido_scanner* scanner)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_scanner_skip_whitespace, scanner);

    if (0 == nondet_status())
    {
        if (0 != *(scanner->input))
        {
            fido_scanner_next_character(scanner);
        }
    }

    MODEL_ASSUME(!isspace(*(scanner->input)));

    retval = (unsigned char)*(scanner->input);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_skip_whitespace, retval, scanner);

    return retval;
}
