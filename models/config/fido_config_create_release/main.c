/**
 * \file models/config/fido_config_create_release/main.c
 *
 * \brief Model checks for fido config create / release.
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
    fido_config* config;

    /* create the config instance. */
    retval = fido_config_create_random(&config);
    if (0 != retval)
    {
        return 1;
    }

    /* release the config instance. */
    fido_config_release(config);

    return 0;
}
