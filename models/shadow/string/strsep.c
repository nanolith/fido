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
size_t strsep_max_runs = 2;

size_t nondet_runs();
int nondet_retval();

size_t random_runs()
{
    size_t val = nondet_runs();
    if (val > strsep_max_runs)
    {
        val = strsep_max_runs;
    }

    return val;
}

char* strsep(char **stringp, const char *delim)
{
    char* str = *stringp;

    if (0 != nondet_retval())
    {
        *stringp = NULL;
        return NULL;
    }

    if (NULL != str)
    {
        __CPROVER_havoc_object(str);
        str[__CPROVER_OBJECT_SIZE(str)-1] = 0;
    }

    if (runs++ >= random_runs())
    {
        *stringp = NULL;
    }

    return str;
}
