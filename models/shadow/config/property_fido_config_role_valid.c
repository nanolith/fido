/**
 * \file models/shadow/config/property_fido_config_role_valid.c
 *
 * \brief Model checking property to ensure that a fido config role is valid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

/**
 * \brief Valid role record.
 *
 * \param role          The role record to check.
 *
 * \returns true if the role record is valid.
 */
bool
property_fido_config_role_valid(
    const fido_config_role* role)
{
    MODEL_CHECK_OBJECT_READ(role, sizeof(*role));

    MODEL_ASSERT(NULL != role->name);

    for (fido_config_command* x = role->command_head;
         NULL != x;
         x = x->next)
    {
        MODEL_ASSERT(property_fido_config_command_valid(x));
    }

    for (fido_config_add_variable* x = role->variable_head;
         NULL != x;
         x = x->next)
    {
        MODEL_ASSERT(property_fido_config_add_variable_valid(x));
    }

    for (fido_config_permission* x = role->permission_head;
         NULL != x;
         x = x->next)
    {
        MODEL_ASSERT(property_fido_config_permission_valid(x));
    }

    return true;
}
