/**
 * \file models/shadow/config/property_fido_config_command_argument_valid.c
 *
 * \brief Model checking property to ensure that a fido command argument is
 * valid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

/**
 * \brief Valid command argument property.
 *
 * \param arg           The command argument to check.
 *
 * \returns true if the command argument is valid.
 */
bool
property_fido_config_command_argument_valid(
    const fido_config_command_argument* arg)
{
    MODEL_CHECK_OBJECT_READ(arg, sizeof(*arg));

    MODEL_ASSERT(NULL != arg->argument_match);

    enum fido_config_command_argument_type at =
        (enum fido_config_command_argument_type)arg->argument_type;
    MODEL_ASSERT(__CPROVER_enum_is_in_range(at));

    return true;
}
