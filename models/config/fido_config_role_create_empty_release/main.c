/**
 * \file models/config/fido_config_role_create_empty_release/main.c
 *
 * \brief Model checks for fido config role create empty / release.
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
    fido_config_role* role;

    /* create the role instance. */
    retval = fido_config_role_create_empty(&role);
    if (0 != retval)
    {
        return 1;
    }

    /* release the role instance. */
    fido_config_role_release(role);

    return 0;
}
