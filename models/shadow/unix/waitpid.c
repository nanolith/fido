/**
 * \file models/shadow/unix/waitpid.c
 *
 * \brief waitpid shadow implementation.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <errno.h>
#include <fcntl.h>
#include <fido/model_assert.h>
#include <fido/properties/unix.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "unix_shadow.h"

pid_t nondet_pid();
int nondet_retval();

pid_t waitpid(pid_t wpid, int* status, int options)
{
    pid_t retval = nondet_pid();
    MODEL_ASSUME(-1 == retval || wpid == retval);

    if (wpid == retval)
    {
        *status = nondet_retval();
        MODEL_ASSUME(WIFEXITED(*status) == 0 || WIFEXITED(*status) == 1);
    }

    return retval;
}
