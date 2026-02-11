/**
 * \file models/shadow/config/fido_scanner_complete_token_identifier.c
 *
 * \brief Shadow implementation of fido_scanner_complete_token_identifer.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>

#include "config/scanner_internal.h"

int nondet_status();

int FN_DECL_MUST_CHECK
fido_scanner_complete_token_identifier(
    fido_token_details* details, fido_scanner* scanner, int type,
    bool read_start)
{
    int retval, peek;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_scanner_complete_token_identifier, details, scanner, type,
        read_start);

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

    retval = fido_scanner_token_details_end(details, scanner, type);
    fido_scanner_next_character(scanner);
    goto done;

hit_eof:
    retval = FIDO_SCANNER_TOKEN_TYPE_EOF;
    goto done;

bad_input:
    retval = FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_complete_token_identifier, retval, details, scanner, type,
        read_start);

    return retval;
}
