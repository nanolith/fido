/**
 * \file models/shadow/unix/close.c
 *
 * \brief close shadow implementation.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/model_assert.h>
#include <fido/properties/unix.h>
#include <unistd.h>

#include "unix_shadow.h"

int nondet_retval();

int close(int fd)
{
    MODEL_ASSERT(property_file_descriptor_open(fd));

    free(shadow_descriptors[fd]);
    shadow_descriptors[fd] = NULL;

    return 0;
}
