/**
 * \file models/shadow/unix/unix_init.c
 *
 * \brief Initialize the Unix shadow system.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/model_assert.h>
#include <stddef.h>

#include "unix_shadow.h"

shadow_file_descriptor* shadow_descriptors[2];

void unix_init()
{
    MODEL_ASSERT(2 == MAX_SHADOW_DESCRIPTORS);

    shadow_descriptors[0] = NULL;
    shadow_descriptors[1] = NULL;
}
