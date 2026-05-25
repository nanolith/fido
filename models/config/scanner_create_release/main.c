/**
 * \file models/config/scanner_create_release/main.c
 *
 * \brief Model checks for fido scanner create / release.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>

int main(int argc, char* argv[])
{
    char input[100];
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

    /* release the scanner instance. */
    fido_scanner_release(scanner);

    return 0;
}
