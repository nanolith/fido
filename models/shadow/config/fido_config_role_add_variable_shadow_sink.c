/**
 * \file models/shadow/config/fido_config_role_add_variable_shadow_sink.c
 *
 * \brief This shadow form of \ref fido_config_role_add_variable is a
 * variable sink.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "config/parser_internal.h"

void
fido_config_role_add_variable(
    fido_config_role* role, fido_config_add_variable* var)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_role_add_variable, role, var);

    fido_config_add_variable_release(var);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_role_add_variable, role, var);
}
