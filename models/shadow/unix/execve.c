/**
 * \file models/shadow/unix/execve.c
 *
 * \brief execve shadow implementation.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <errno.h>
#include <fido/model_assert.h>
#include <unistd.h>

#include "unix_shadow.h"

int nondet_retval();

int
execve(const char *path, char *const argv[], char *const envp[])
{
    int retval = nondet_retval();
    MODEL_ASSUME(0 == retval || -1 == retval);

    /* we never return if execve succeeds. */
    if (0 == retval)
    {
        /* trim this branch of the decision tree. */
        MODEL_ASSUME(0);
    }

    /* otherwise, set the error number. */
    errno = nondet_retval();
    MODEL_ASSUME(ENOEXEC == errno || ENOENT == errno || EACCES == errno);

    return retval;
}
