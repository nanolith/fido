/**
 * \file config/fido_config_add_variable_create.c
 *
 * \brief Create a \ref fido_config_add_variable instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

/**
 * \brief Create a \ref fido_config_add_variable instance.
 *
 * \param var               Pointer to the variable pointer to set to this
 *                          created instance on success.
 * \param name              The name of the variable to add.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_add_variable_create(
    fido_config_add_variable** var, const char* name)
{
    int retval;
    fido_config_add_variable* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_add_variable_create, var, name);

    /* allocate memory for this variable. */
    tmp = (fido_config_add_variable*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto error_exit;
    }

    /* set up variable. */
    memset(tmp, 0, sizeof(*tmp));

    /* copy variable name. */
    tmp->name = strdup(name);
    if (NULL == tmp->name)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    /* success. */
    *var = tmp;
    retval = 0;
    goto done;

cleanup_tmp:
    fido_config_add_variable_release(tmp);

error_exit:
    *var = NULL;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_add_variable_create, retval, var, name);

    return retval;
}
