/**
 * \file models/shadow/unix/sysconf.c
 *
 * \brief Fido specific shadow method for sysconf.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/model_assert.h>
#include <unistd.h>

long nondet_long();

long choose_size()
{
    long val = nondet_long();
    MODEL_ASSUME(val == -1 || (val > 0 && val <= 32768));

    return val;
}

long choose_ngroups()
{
    long val = nondet_long();
    MODEL_ASSUME(val >= 0 && val <= 3);

    return val;
}

long sysconf(int name)
{
    switch (name)
    {
        case _SC_NGROUPS_MAX:
            return choose_ngroups();

        case _SC_GETGR_R_SIZE_MAX:
        case _SC_GETPW_R_SIZE_MAX:
            return choose_size();

        default:
            return -1;
    }
}
