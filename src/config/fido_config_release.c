/**
 * \file config/fido_config_release.c
 *
 * \brief Release a \ref fido_config instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Release a \ref fido_config instance.
 *
 * \param config        The config record to release.
 */
void
fido_config_release(fido_config* config)
{
    fido_config_role* role;
    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_config_release, config);

    /* clean up roles. */
    while (NULL != config->head)
    {
        role = config->head->next;
        fido_config_role_release(config->head);
        config->head = role;
    }

    free(config);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_config_release, config);
}
