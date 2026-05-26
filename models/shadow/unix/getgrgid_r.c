/**
 * \file models/shadow/unix/getgrid_r.c
 *
 * \brief Fido specific shadow method for getgrgid_r.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/model_assert.h>
#include <grp.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

int nondet_retval();
gid_t nondet_gid();

gid_t choose_gid()
{
    gid_t val = nondet_gid();
    MODEL_ASSUME(val >= 0 && val < INT16_MAX);

    return val;
}

char name[8];

int
getgrgid_r(
    gid_t gid, struct group *grp, char *buffer, size_t bufsize,
    struct group **result)
{
    int retval = nondet_retval();

    if (0 == retval)
    {
        if (0 == nondet_retval())
        {
            __CPROVER_havoc_object(name);
            name[sizeof(name)-1] = 0;

            *result = grp;
            memset(grp, 0, sizeof(*grp));
            grp->gr_gid = choose_gid();
            grp->gr_name = name;
        }
        else
        {
            *result = NULL;
        }
    }

    return retval;
}
