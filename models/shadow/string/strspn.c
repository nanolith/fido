/**
 * \file models/shadow/string/strspn.c
 *
 * \brief Shadow implementation of strspn. This version just returns a
 * non-deterministic span; it should only be used for membership testing.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <string.h>

size_t nondet_span();

size_t strspn(const char* s, const char* charset)
{
    return nondet_span();
}
