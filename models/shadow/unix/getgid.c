/**
 * \file models/shadow/unix/getgid.c
 *
 * \brief Shadow method for getgid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/model_assert.h>
#include <stdint.h>
#include <unistd.h>

gid_t nondet_gid();

gid_t choose_gid()
{
    gid_t val = nondet_gid();
    MODEL_ASSUME(val >= 0 && val <= INT16_MAX);

    return val;
}

gid_t getgid()
{
    return choose_gid();
}
