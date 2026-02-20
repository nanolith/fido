/**
 * \file config/fido_config_role_create.c
 *
 * \brief Create a \ref fido_config_role instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

/**
 * \brief Create a \ref fido_config_role instance.
 *
 * \param role              Pointer to the role pointer to set to this
 *                          created instance on success.
 * \param name              The name of the role.
 * \param as_user           Optional "as user" attribute or NULL.
 * \param as_group          Optional "as group" attribute or NULL.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_role_create(
    fido_config_role** role, const char* name, const char* as_user,
    const char* as_group)
{
    int retval;
    fido_config_role* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_role_create, role, name, as_user, as_group);

    /* allocate memory for this role. */
    tmp = (fido_config_role*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto error_exit;
    }

    /* set up role. */
    memset(tmp, 0, sizeof(*tmp));

    /* copy role name. */
    tmp->name = strdup(name);
    if (NULL == tmp->name)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    /* copy as_user. */
    if (NULL != as_user)
    {
        tmp->as_user = strdup(as_user);
        if (NULL == tmp->as_user)
        {
            retval = FIDO_ERROR_OUT_OF_MEMORY;
            goto cleanup_tmp;
        }
    }

    /* copy as_group. */
    if (NULL != as_group)
    {
        tmp->as_group = strdup(as_group);
        if (NULL == tmp->as_group)
        {
            retval = FIDO_ERROR_OUT_OF_MEMORY;
            goto cleanup_tmp;
        }
    }

    /* success. */
    *role = tmp;
    retval = 0;
    goto done;

cleanup_tmp:
    fido_config_role_release(tmp);

error_exit:
    *role = NULL;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_role_create, retval, role, name, as_user, as_group);

    return retval;
}
