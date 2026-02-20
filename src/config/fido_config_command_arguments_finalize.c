/**
 * \file config/fido_config_command_arguments_finalize.c
 *
 * \brief Finalize arguments for a \ref fido_config_command instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Finalize arguments for a \ref fido_config_command instance.
 *
 * \param cmd               The command instance for this operation.
 */
void
fido_config_command_arguments_finalize(fido_config_command* cmd)
{
    fido_config_command_argument* head = NULL;
    fido_config_command_argument* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_command_arguments_finalize, cmd);

    while (NULL != cmd->head)
    {
        /* cache next. */
        tmp = cmd->head->next;

        /* detach cmd->head from list and attach to new list. */
        cmd->head->next = head;

        /* update new list head to point to cmd->head. */
        head = cmd->head;

        /* move cmd->head to the next item in the original list. */
        cmd->head = tmp;
    }

    /* assign cmd->head to the reversed list. */
    cmd->head = head;

    /* the arguments are now finalized. */
    cmd->arguments_finalized = true;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_command_arguments_finalize, cmd);
}
