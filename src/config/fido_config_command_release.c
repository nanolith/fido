/**
 * \file config/fido_config_command_release.c
 *
 * \brief Release a \ref fido_config_command instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Release a \ref fido_config_command instance.
 *
 * \param cmd           The command to release.
 */
void fido_config_command_release(fido_config_command* cmd)
{
    fido_config_command_argument* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_config_command_release, cmd);

    /* clean up binary if set. */
    if (NULL != cmd->binary)
    {
        free(cmd->binary);
    }

    /* clean up all arguments. */
    while (NULL != cmd->head)
    {
        tmp = cmd->head->next;
        fido_config_command_argument_release(cmd->head);
        cmd->head = tmp;
    }

    free(cmd);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_config_command_release, cmd);
}
