/**
 * \file models/shadow/unix/getuid.c
 *
 * \brief Shadow method for getuid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/model_assert.h>
#include <stdint.h>
#include <unistd.h>

uid_t nondet_uid();

uid_t choose_uid()
{
    uid_t val = nondet_uid();
    MODEL_ASSUME(val >= 0 && val <= INT16_MAX);

    return val;
}

uid_t getuid()
{
    return choose_uid();
}
