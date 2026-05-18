/**
 * \file config/fido_config_role_as_group_set.c
 *
 * \brief Set the \ref fido_config_role as_group to the given value.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

/**
 * \brief Set the as group of the role to the given value.
 *
 * \param role              The role for this operation.
 * \param as_group          The new as_group for this role.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_role_as_group_set(fido_config_role* role, const char* as_group)
{
    int retval;
    char* new_as_group;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_role_as_group_set, role, as_group);

    /* duplicate the new as_group. */
    new_as_group = strdup(as_group);
    if (NULL == new_as_group)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* free the old as_group if set. */
    if (NULL != role->as_group)
    {
        free(role->as_group);
    }

    /* assign the new as_group. */
    role->as_group = new_as_group;
    retval = 0;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_role_as_group_set, retval, role, as_group);

    return retval;
}
