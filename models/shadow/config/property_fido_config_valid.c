/**
 * \file models/shadow/config/property_fido_config_valid.c
 *
 * \brief Model checking property to ensure that a fido config is valid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

/**
 * \brief Valid config record.
 *
 * \param config        The config record to check.
 *
 * \returns true if the config record is valid.
 */
bool
property_fido_config_valid(
    const fido_config* config)
{
    MODEL_CHECK_OBJECT_READ(config, sizeof(*config));

    for (
        fido_config_role* x = config->head;
        NULL != x;
        x = x->next)
    {
        MODEL_ASSERT(property_fido_config_role_valid(x));
    }

    return true;
}
