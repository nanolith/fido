/**
 * \file models/shadow/unix/open.c
 *
 * \brief open shadow implementation.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <errno.h>
#include <fcntl.h>
#include <fido/model_assert.h>
#include <fido/properties/unix.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>

#include "unix_shadow.h"

int nondet_retval();

int open(const char *path, int flags, ...)
{
    MODEL_ASSERT(NULL != path);
    MODEL_ASSERT(O_RDONLY == flags);

    int retval = nondet_retval();
    MODEL_ASSUME(
        -1 == retval || (retval >= 0 && retval < MAX_SHADOW_DESCRIPTORS));

    if (retval >= 0)
    {
        if (NULL == shadow_descriptors[retval])
        {
            shadow_descriptors[retval] =
                (shadow_file_descriptor*)malloc(sizeof(shadow_file_descriptor));
            if (NULL == shadow_descriptors[retval])
            {
                retval = -1;
            }
            else
            {
                shadow_descriptors[retval]->mode = SHADOW_FILE_DESCRIPTOR_OPEN;
            }
        }
    }

    if (retval < 0)
    {
        errno = nondet_retval();
        MODEL_ASSUME(EPERM == errno || ENOENT == errno);
    }

    return retval;
}
