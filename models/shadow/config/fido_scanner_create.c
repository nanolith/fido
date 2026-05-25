/**
 * \file models/shadow/config/fido_scanner_create.c
 *
 * \brief fido_scanner_create shadow impl.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>

char global_input[10];

int FN_DECL_MUST_CHECK
fido_scanner_create(fido_scanner** scanner, const char* input)
{
    int retval;
    __CPROVER_havoc_object(global_input);
    global_input[sizeof(global_input)-1] = 0;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_scanner_create, scanner, input);

    *scanner = NULL;

    fido_scanner* tmp = (fido_scanner*)malloc(sizeof(fido_scanner));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    tmp->original_input = global_input;
    tmp->input = global_input;
    tmp->index = 0;
    tmp->line = 1;
    tmp->col = 1;

    retval = 0;
    *scanner = tmp;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_scanner_create, retval, scanner, global_input);

    return retval;
}
