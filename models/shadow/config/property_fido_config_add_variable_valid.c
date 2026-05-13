/**
 * \file models/shadow/config/property_fido_config_add_variable_valid.c
 *
 * \brief Model checking property to ensure that a fido config add variable is
 * valid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

/**
 * \brief Valid add variable record.
 *
 * \param var           The add variable record to check.
 *
 * \returns true if the add variable record is valid.
 */
bool
property_fido_config_add_variable_valid(
    const fido_config_add_variable* var)
{
    MODEL_CHECK_OBJECT_READ(var, sizeof(*var));

    MODEL_ASSERT(NULL != var->name);

    return true;
}
