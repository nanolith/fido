/**
 * \file models/shadow/config/fido_config_role_add_permission_shadow_sink.c
 *
 * \brief This shadow form of \ref fido_config_role_add_permission is a
 * permission sink.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "config/parser_internal.h"

void
fido_config_role_add_permission(
    fido_config_role* role, fido_config_permission* perm)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_role_add_permission, role, perm);

    fido_config_permission_release(perm);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_role_add_permission, role, perm);
}
