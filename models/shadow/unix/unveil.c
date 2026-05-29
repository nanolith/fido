/**
 * \file models/shadow/unix/unveil.c
 *
 * \brief Shadow method for unveil.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/model_assert.h>
#include <stdint.h>
#include <unistd.h>

int nondet_retval();

int unveil(const char* path, const char* permissions)
{
    int retval = nondet_retval();
    MODEL_ASSUME(0 == retval || -1 == retval);

    return retval;
}
