/**
 * \file models/shadow/unix/getgroups.c
 *
 * \brief Fido specific shadow method for getgroups.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/model_assert.h>
#include <stdint.h>
#include <unistd.h>

int nondet_int();
gid_t nondet_gid();

int choose_gidsetlen()
{
    int val = nondet_int();
    MODEL_ASSUME(val > 0 && val <= 3);
    return val;
}

gid_t choose_gid()
{
    gid_t val = nondet_gid();
    MODEL_ASSUME(val >= 0 && val < INT16_MAX);
    return val;
}

int getgroups(int gidsetlen, gid_t *gidset)
{
    int retlen = choose_gidsetlen();
    if (retlen > gidsetlen)
        retlen = gidsetlen;

    if (retlen > 0) gidset[0] = choose_gid();
    if (retlen > 1) gidset[1] = choose_gid();
    if (retlen > 2) gidset[2] = choose_gid();

    return retlen;
}
