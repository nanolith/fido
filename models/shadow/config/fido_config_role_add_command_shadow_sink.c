/**
 * \file models/shadow/config/fido_config_role_add_command_shadow_sink.c
 *
 * \brief This shadow form of \ref fido_config_role_add_command is a command
 * sink.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "config/parser_internal.h"

void
fido_config_role_add_command(
    fido_config_role* role, fido_config_command* cmd)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_role_add_command, role, cmd);

    fido_config_command_release(cmd);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_role_add_command, role, cmd);
}
