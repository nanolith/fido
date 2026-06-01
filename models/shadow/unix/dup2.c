/**
 * \file models/shadow/unix/dup2.c
 *
 * \brief dup2 shadow implementation. This implementation is basically a no-op
 * that returns a non-deterministic return value and sets errno on error.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <errno.h>
#include <fido/model_assert.h>
#include <unistd.h>

#include "unix_shadow.h"

int nondet_retval();

int dup2(int oldd, int newd)
{
    int retval = nondet_retval();
    MODEL_ASSUME(-1 == retval || retval >= 0);

    if (retval < 0)
    {
        errno = nondet_retval();
        MODEL_ASSUME(EBADF == errno || EMFILE == errno);
    }

    return retval;
}
