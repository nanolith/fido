/**
 * \file config/fido_scanner_release.c
 *
 * \brief Release a scanner instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief Release a \ref fido_scanner instance.
 *
 * \param scanner           The scanner to release.
 */
void
fido_scanner_release(fido_scanner* scanner)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_scanner_release, scanner);

    memset(scanner, 0, sizeof(*scanner));
    free(scanner);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_scanner_release, scanner);
}
