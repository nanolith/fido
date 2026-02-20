/**
 * \file config/fido_config_role_permissions_finalize.c
 *
 * \brief Finalize permissions for a \ref fido_config_role instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Finalize permissions for a \ref fido_config_role instance.
 *
 * \param role              The role instance for this operation.
 */
void
fido_config_role_permissions_finalize(fido_config_role* role)
{
    fido_config_permission* head = NULL;
    fido_config_permission* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_role_permissions_finalize, role);

    while (NULL != role->permission_head)
    {
        /* cache next. */
        tmp = role->permission_head->next;

        /* detach role->permission_head from list and attach to new list. */
        role->permission_head->next = head;

        /* update new list head to point to role->permission_head. */
        head = role->permission_head;

        /* move role->permission_head to the next item in the original list. */
        role->permission_head = tmp;
    }

    /* assign role->permission_head to the reversed list. */
    role->permission_head = head;

    /* the permissions are now finalized. */
    role->permissions_finalized = true;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_role_permissions_finalize, role);
}
