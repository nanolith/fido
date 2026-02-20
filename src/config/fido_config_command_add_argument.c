/**
 * \file config/fido_config_command_add_argument.c
 *
 * \brief Add an argument to the \ref fido_config_command instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Add an argument to the \ref fido_config_command instance.
 *
 * \param cmd               The command instance for this operation.
 * \param arg               The argument to add.
 */
void
fido_config_command_add_argument(
    fido_config_command* cmd, fido_config_command_argument* arg)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_command_add_argument, cmd, arg);

    arg->next = cmd->head;
    cmd->head = arg;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_command_add_argument, cmd, arg);
}
