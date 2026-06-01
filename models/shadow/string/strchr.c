/**
 * \file models/shadow/string/strchr.c
 *
 * \brief Shadow implementation of \ref strchr.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <string.h>

size_t nondet_size();

char* strchr(const char* s, int c)
{
    size_t string_size = __CPROVER_OBJECT_SIZE(s);
    size_t sz = nondet_size();

    if (sz > string_size-1)
    {
        return NULL;
    }

    return s + sz;
}
