/**
 * \file models/shadow/unix/read.c
 *
 * \brief read shadow implementation.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <errno.h>
#include <fido/model_assert.h>
#include <fido/properties/unix.h>
#include <unistd.h>

#include "unix_shadow.h"

ssize_t nondet_size();
int nondet_errno();

ssize_t read(int fd, void *buf, size_t nbytes)
{
    ssize_t retval = nondet_size();
    MODEL_ASSUME(-1 == retval || retval <= nbytes);

    __CPROVER_havoc_object(buf);

    if (retval < 0)
    {
        errno = nondet_errno();
        MODEL_ASSUME(EBADF == errno || EINTR == errno || EISDIR == errno);
    }

    return retval;
}
