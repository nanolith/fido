/**
 * \file models/shadow/path/fido_path_resolve.c
 *
 * \brief Shadow implementation of \ref fido_path_resolve.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/path.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int nondet_retval();

int FN_DECL_MUST_CHECK
fido_path_resolve(char** resolved, const char* input_path, const char* command)
{
    char cmd[8];

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_path_resolve, resolved, input_path, command);

    int retval = nondet_retval();
    enum fido_error_code ec = (enum fido_error_code)retval;
    MODEL_ASSUME(retval = 0 || __CPROVER_enum_is_in_range(ec));

    if (0 == retval)
    {
        __CPROVER_havoc_object(cmd);
        cmd[sizeof(cmd)-1] = 0;
        *resolved = strdup(cmd);
        if (NULL == *resolved)
        {
            /* trim decision path where strdup fails. */
            MODEL_ASSUME(0);
        }
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_path_resolve, retval, resolved, input_path, command);

    return retval;
}
