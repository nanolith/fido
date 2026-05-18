/**
 * \file config/fido_config_role_name_set.c
 *
 * \brief Set the \ref fido_config_role name to the given value.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

/**
 * \brief Set the name of the role to the given value.
 *
 * \param role              The role for this operation.
 * \param name              The new name for this role.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_role_name_set(fido_config_role* role, const char* name)
{
    int retval;
    char* new_name;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_config_role_name_set, role, name);

    /* duplicate the new name. */
    new_name = strdup(name);
    if (NULL == new_name)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* free the old name if set. */
    if (NULL != role->name)
    {
        free(role->name);
    }

    /* assign the new name. */
    role->name = new_name;
    retval = 0;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_role_name_set, retval, role, name);

    return retval;
}
