/**
 * \file models/shadow/config/fido_config_add_role_shadow_sink.c
 *
 * \brief This shadow form of \ref fido_config_add_role is a role sink.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "config/parser_internal.h"

void
fido_config_add_role(
    fido_config* config, fido_config_role* role)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_config_add_role, config, role);

    fido_config_role_release(role);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_config_add_role, config, role);
}
