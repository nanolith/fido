/**
 * \file models/shadow/string/strsep.c
 *
 * \brief Shadow implementation of \ref strsep that is strictly terminating.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <string.h>

size_t runs = 0;

size_t nondet_runs();

size_t random_runs()
{
    size_t val = nondet_runs();
    if (val > 2)
    {
        val = 2;
    }

    return val;
}

char* strsep(char **stringp, const char *delim)
{
    char* str = *stringp;

    if (runs++ >= random_runs())
    {
        *stringp = NULL;
    }

    return str;
}
