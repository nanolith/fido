/**
 * \file config/fido_config_create.c
 *
 * \brief Create a \ref fido_config instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

/**
 * \brief Create a \ref fido_config instance.
 *
 * \param config            Pointer to the config pointer to set to this
 *                          created instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_create(fido_config** config)
{
    int retval;
    fido_config* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_config_create, config);

    /* allocate memory for this config. */
    tmp = (fido_config*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto error_exit;
    }

    /* set up config. */
    memset(tmp, 0, sizeof(*tmp));

    /* success. */
    *config = tmp;
    retval = 0;
    goto done;

error_exit:
    *config = NULL;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_config_create, retval, config);

    return retval;
}
