/**
 * \file models/shadow/unix/fork.c
 *
 * \brief fork shadow implementation.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <errno.h>
#include <fido/model_assert.h>
#include <unistd.h>

#include "unix_shadow.h"

pid_t nondet_pid();
int nondet_errno();

pid_t fork(void)
{
    pid_t pid = nondet_pid();
    MODEL_ASSUME(-1 == pid || pid >= 0);

    if (pid < 0)
    {
        errno = nondet_errno();
        MODEL_ASSUME(EAGAIN == errno || ENOMEM == errno);
    }

    return pid;
}
