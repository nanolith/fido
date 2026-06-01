/**
 * \file models/shadow/unix/pipe.c
 *
 * \brief pipe shadow implementation.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <errno.h>
#include <fcntl.h>
#include <fido/model_assert.h>
#include <unistd.h>

#include "unix_shadow.h"

int nondet_retval();

int pipe(int filedes[2])
{
    int retval = nondet_retval();
    MODEL_ASSUME(0 == retval || -1 == retval);

    if (retval < 0)
    {
        errno = nondet_retval();
        MODEL_ASSUME(EFAULT == errno || EMFILE == errno || ENOMEM == retval);
        return retval;
    }

    filedes[0] = open("foo.in", O_RDONLY);
    if (filedes[0] < 0)
    {
        /* trim this branch. */
        MODEL_ASSUME(0);
    }

    filedes[1] = open("foo.out", O_RDONLY);
    if (filedes[1] < 0)
    {
        /* trim this branch. */
        MODEL_ASSUME(0);
    }

    return 0;
}
