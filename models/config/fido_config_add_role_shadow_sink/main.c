/**
 * \file models/config/fido_config_add_role_shadow_sink/main.c
 *
 * \brief Model checks for \ref fido_config_add_role_shadow_sink.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

#include "../../helpers/config/config_helpers.h"
#include "config/parser_internal.h"

int main(int argc, char* argv[])
{
    int retval;
    fido_config* config = NULL;
    fido_config_role* role = NULL;

    /* create the config instance. */
    retval = fido_config_create_random(&config);
    if (0 != retval)
    {
        goto done;
    }

    /* create the role instance. */
    retval = fido_config_role_create_random(&role);
    if (0 != retval)
    {
        goto cleanup_config;
    }

    /* add the role to config. */
    fido_config_add_role(config, role);

    /* release the config instance. */
    goto cleanup_config;

cleanup_config:
    fido_config_release(config);

done:
    return retval;
}
