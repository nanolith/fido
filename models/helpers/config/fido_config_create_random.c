/**
 * \file models/helpers/config/fido_config_create_random.c
 *
 * \brief Non-deterministic config create helper.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "config_helpers.h"

int FN_DECL_MUST_CHECK
fido_config_create_random(fido_config** conf)
{
    /* create the config instance. */
    return fido_config_create(conf);
}
