/**
 * \file config/fido_config_command_argument_release.c
 *
 * \brief Release a \ref fido_config_command_argument instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Release a \ref fido_config_command_argument instance.
 *
 * \param arg           The argument to release.
 */
void fido_config_command_argument_release(fido_config_command_argument* arg)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_command_argument_release, arg);

    /* clean up argument_match if set. */
    if (NULL != arg->argument_match)
    {
        free(arg->argument_match);
    }

    free(arg);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_command_argument_release, arg);
}
