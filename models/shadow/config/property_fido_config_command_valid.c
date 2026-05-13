/**
 * \file models/shadow/config/property_fido_config_command_valid.c
 *
 * \brief Model checking property to ensure that a fido config command is
 * valid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

/**
 * \brief Valid command record property.
 *
 * \param cmd           The command record to check.
 *
 * \returns true if the command record is valid.
 */
bool
property_fido_config_command_valid(
    const fido_config_command* cmd)
{
    MODEL_CHECK_OBJECT_READ(cmd, sizeof(*cmd));

    MODEL_ASSERT(NULL != cmd->binary);

    for (
        fido_config_command_argument* x = cmd->head;
        NULL != x;
        x = x->next)
    {
        MODEL_ASSERT(property_fido_config_command_argument_valid(x));
    }

    return true;
}
