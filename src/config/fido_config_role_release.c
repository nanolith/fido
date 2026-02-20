/**
 * \file config/fido_config_role_release.c
 *
 * \brief Release a \ref fido_config_role instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Release a \ref fido_config_role instance.
 *
 * \param role          The role instance to release.
 */
void fido_config_role_release(fido_config_role* role)
{
    fido_config_command* cmd;
    fido_config_add_variable* var;
    fido_config_permission* perm;
    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_config_role_release, role);

    /* clean up name if set. */
    if (NULL != role->name)
    {
        free(role->name);
    }

    /* clean up as_user if set. */
    if (NULL != role->as_user)
    {
        free(role->as_user);
    }

    /* clean up as_group if set. */
    if (NULL != role->as_group)
    {
        free(role->as_group);
    }

    /* clean up commands. */
    while (NULL != role->command_head)
    {
        cmd = role->command_head->next;
        fido_config_command_release(role->command_head);
        role->command_head = cmd;
    }

    /* clean up variables. */
    while (NULL != role->variable_head)
    {
        var = role->variable_head->next;
        fido_config_add_variable_release(role->variable_head);
        role->variable_head = var;
    }

    /* clean up permissions. */
    while (NULL != role->permission_head)
    {
        perm = role->permission_head->next;
        fido_config_permission_release(role->permission_head);
        role->permission_head = perm;
    }

    free(role);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_config_role_release, role);
}
