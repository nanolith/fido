/**
 * \file models/config/fido_config_permission_create_release/main.c
 *
 * \brief Model checks for fido config permission create / release.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

#include "config/parser_internal.h"

int main(int argc, char* argv[])
{
    int retval;
    fido_config_permission* perm;

    /* create the permission instance. */
    retval = fido_config_permission_create_random(&perm);
    if (0 != retval)
    {
        return 1;
    }

    /* release the permission instance. */
    fido_config_permission_release(perm);

    return 0;
}
