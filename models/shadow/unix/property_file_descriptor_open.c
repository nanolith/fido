/**
 * \file models/shadow/unix/property_file_descriptor_open.c
 *
 * \brief Check to see if a file descriptor is open.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/model_assert.h>
#include <stdbool.h>

#include "unix_shadow.h"

/**
 * \brief Open file descriptor property.
 *
 * \param fd            The file descriptor to check.
 *
 * \returns true if the file descriptor is open.
 */
bool property_file_descriptor_open(int fd)
{
    MODEL_ASSERT(fd >= 0 && fd < MAX_SHADOW_DESCRIPTORS);
    MODEL_CHECK_OBJECT_READ(
        shadow_descriptors[fd], sizeof(shadow_file_descriptor));
    MODEL_ASSERT(shadow_descriptors[fd]->mode & SHADOW_FILE_DESCRIPTOR_OPEN);

    return true;
}
