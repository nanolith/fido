/**
 * \file config/fido_scanner_create.c
 *
 * \brief Create a scanner instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "scanner_internal.h"

/**
 * \brief Create a \ref fido_scanner instance.
 *
 * \param scanner           Pointer to the scanner pointer to be set to this
 *                          created scanner instance on success.
 * \param input             The input string to scan.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_scanner_create(fido_scanner** scanner, const char* input)
{
    int retval;
    fido_scanner* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_scanner_create, scanner, input);

    /* allocate memory for this instance. */
    tmp = (fido_scanner*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        *scanner = NULL;
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* initialize tmp. */
    memset(tmp, 0, sizeof(*tmp));
    tmp->original_input = tmp->input = input;
    tmp->index = 0;
    tmp->line = tmp->col = 1;

    /* success. */
    *scanner = tmp;
    retval = 0;
    goto done;

done:
    if (0 != retval)
    {
        *scanner = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_create, retval, scanner, input);

    return retval;
}
