/**
 * \file models/shadow/unix/realpath.c
 *
 * \brief Shadow method for realpath.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/model_assert.h>
#include <stdlib.h>
#include <string.h>

char *realpath(const char *pathname, char *resolved_path)
{
    MODEL_ASSERT(NULL == resolved_path);

    return strdup(pathname);
}
