/**
 * \file models/shadow/config/property_fido_scanner_valid.c
 *
 * \brief Model checking property to ensure that a scanner instance is valid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>

/**
 * \brief Valid scanner property.
 *
 * \param scanner       The scanner instance to be verified.
 *
 * \returns true if the scanner instance is valid.
 */
bool
property_fido_scanner_valid(
    const fido_scanner* scanner)
{
    MODEL_CHECK_OBJECT_READ(scanner, sizeof(*scanner));
    MODEL_CHECK_OBJECT_READ(scanner->original_input + scanner->index, 1);
    MODEL_CHECK_OBJECT_READ(scanner->input, 1);
    MODEL_ASSERT(NULL != scanner->original_input);
    MODEL_ASSERT(NULL != scanner->input);
    MODEL_ASSERT(scanner->line >= 1);
    MODEL_ASSERT(scanner->col >= 1);

    return true;
}
