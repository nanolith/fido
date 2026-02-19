/**
 * \file config/fido_config_permission_create.c
 *
 * \brief Create a \ref fido_config_permission instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

/**
 * \brief Create a \ref fido_config_permission instance.
 *
 * \param perm              Pointer to the permission pointer to set to this
                            created instance on success.
 * \param identifier        The identifier name.
 * \param identifier_type   The identifier type. \see
 *                          \ref fido_config_identifier_type.
 * \param permission_type   The permission type. \see
 *                          \ref fido_config_permission_type.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_permission_create(
    fido_config_permission** perm, const char* identifier, int identifier_type,
    int permission_type)
{
    int retval;
    fido_config_permission* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_permission_release, perm, identifier, identifier_type,
        permission_type);

    /* allocate memory for this permission. */
    tmp = (fido_config_permission*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto error_exit;
    }

    /* set up permission. */
    memset(tmp, 0, sizeof(*tmp));
    tmp->identifier_type = identifier_type;
    tmp->permission_type = permission_type;

    /* copy identifier. */
    tmp->identifier = strdup(identifier);
    if (NULL == tmp->identifier)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    /* success. */
    *perm = tmp;
    retval = 0;
    goto done;

cleanup_tmp:
    fido_config_permission_release(tmp);

error_exit:
    *perm = NULL;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_permission_create, retval, perm, identifier,
        identifier_type, permission_type);

    return retval;
}
