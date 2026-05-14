/**
 * \file models/shadow/config/fido_config_command_add_argument_shadow_sink.c
 *
 * \brief This shadow form of \ref fido_config_command_add_argument is an
 * argument sink.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "config/parser_internal.h"

void
fido_config_command_add_argument(
    fido_config_command* cmd, fido_config_command_argument* arg)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_command_add_argument, cmd, arg);

    fido_config_command_argument_release(arg);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_command_add_argument, cmd, arg);
}
