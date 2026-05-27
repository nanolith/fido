/**
 * \file test/policy/helpers.cpp
 *
 * \brief Helper methods for policy unit tests.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "helpers.h"

int fido_options_create_test(
    fido_options** opts, const char* binary_name, size_t arguments_count,
    const char** arguments)
{
    int retval;
    fido_options* tmp;

    tmp = (fido_options*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* set up tmp. */
    memset(tmp, 0, sizeof(*tmp));
    tmp->binary_name = binary_name;
    tmp->arguments_count = arguments_count;
    tmp->arguments = arguments;

    /* success. */
    retval = 0;
    *opts = tmp;
    goto done;

done:
    return retval;
}
