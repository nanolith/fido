/**
 * \file config/fido_config_role_as_user_set.c
 *
 * \brief Set the \ref fido_config_role as_user to the given value.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

/**
 * \brief Set the as user of the role to the given value.
 *
 * \param role              The role for this operation.
 * \param as_user           The new as_user for this role.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_role_as_user_set(fido_config_role* role, const char* as_user)
{
    int retval;
    char* new_as_user;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_role_as_user_set, role, as_user);

    /* duplicate the new as_user. */
    new_as_user = strdup(as_user);
    if (NULL == new_as_user)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* free the old as_user if set. */
    if (NULL != role->as_user)
    {
        free(role->as_user);
    }

    /* assign the new as_user. */
    role->as_user = new_as_user;
    retval = 0;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_role_as_user_set, retval, role, as_user);

    return retval;
}
