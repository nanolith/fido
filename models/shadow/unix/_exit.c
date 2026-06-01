/**
 * \file models/shadow/unix/_exit.c
 *
 * \brief _exit shadow implementation.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <errno.h>
#include <fido/model_assert.h>
#include <unistd.h>

#include "unix_shadow.h"

void _exit(int status)
{
    /* there is no return from this function, so trim it from the decision
     * tree. */
    MODEL_ASSUME(0);
}
