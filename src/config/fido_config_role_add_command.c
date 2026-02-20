/**
 * \file config/fido_config_role_add_command.c
 *
 * \brief Add a command to the \ref fido_config_role instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Add a command to a role instance.
 *
 * \param role              The role instance for this operation.
 * \param cmd               The command to add.
 */
void
fido_config_role_add_command(
    fido_config_role* role, fido_config_command* cmd)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_role_add_command, role, cmd);

    cmd->next = role->command_head;
    role->command_head = cmd;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_role_add_command, role, cmd);
}
