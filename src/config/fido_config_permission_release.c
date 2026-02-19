/**
 * \file config/fido_config_permission_release.c
 *
 * \brief Release a \ref fido_config_permission instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Release a \ref fido_config_permission instance.
 *
 * \param perm          The permission to release.
 */
void fido_config_permission_release(fido_config_permission* perm)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_config_permission_release, perm);

    /* clean up identifier if set. */
    if (NULL != perm->identifier)
    {
        free(perm->identifier);
    }

    free(perm);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_config_permission_release, perm);
}
