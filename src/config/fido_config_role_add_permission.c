/**
 * \file config/fido_config_role_add_permission.c
 *
 * \brief Add a permission to the \ref fido_config_role instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Add a permission to a role instance.
 *
 * \param role              The role instance for this operation.
 * \param perm              The permission to add.
 */
void
fido_config_role_add_permission(
    fido_config_role* role, fido_config_permission* perm)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_role_add_permission, role, perm);

    perm->next = role->permission_head;
    role->permission_head = perm;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_role_add_permission, role, perm);
}
