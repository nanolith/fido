/**
 * \file models/shadow/config/fido_scanner_read_token.c
 *
 * \brief fido_scanner_read_token shadow impl.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>

#include "config/scanner_internal.h"

int nondet_int();

static int choose_enum()
{
    enum fido_scanner_token_type retval =
        (enum fido_scanner_token_type)nondet_int();

    MODEL_ASSUME(__CPROVER_enum_is_in_range(retval));

    return retval;
};

int FN_DECL_MUST_CHECK
fido_scanner_read_token(
    fido_token_details* details, fido_scanner* scanner)
{
    int retval, ch;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_scanner_read_token, details, scanner);

    if (0 == nondet_status())
    {
        ch = *(scanner->input);
        if (0 == ch)
            goto hit_eof;

        fido_scanner_token_details_begin(details, scanner);

        fido_scanner_next_character(scanner);
        if (0 == *(scanner->input))
            goto hit_eof;
    }
    else
    {
        goto bad_input;
    }

    retval = fido_scanner_token_details_end(details, scanner, choose_enum());
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
        fido_scanner_read_token, retval, details, scanner);

    return retval;
}
