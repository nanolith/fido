/**
 * \file models/shadow/unix/cap_rights_limit.c
 *
 * \brief Shadow method for cap_rights_limit.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/model_assert.h>
#include <stdint.h>
#include <sys/capsicum.h>
#include <unistd.h>

int nondet_retval();

int cap_rights_limit(int fd, const cap_rights_t* rights)
{
    int retval = nondet_retval();
    MODEL_ASSUME(0 == retval || -1 == retval);

    return retval;
}
