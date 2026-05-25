/**
 * \file models/config/fido_scanner_skip_whitespace_shadow/main.c
 *
 * \brief Model checks for fido_scanner_skip_whitespace_shadow.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>

#include "config/scanner_internal.h"

int main(int argc, char* argv[])
{
    char input[10];
    int retval;
    fido_scanner* scanner;

    /* randomize input, and ensure it is ASCIIZ. */
    __CPROVER_havoc_object(input);
    input[sizeof(input)-1] = 0;

    /* create the scanner instance. */
    retval = fido_scanner_create(&scanner, input);
    if (0 != retval)
    {
        return 1;
    }

    /* get the next character that is not whitespace. */
    retval = fido_scanner_skip_whitespace(scanner);
    MODEL_ASSERT(!isspace(retval));

    /* release the scanner instance. */
    fido_scanner_release(scanner);

    return 0;
}
