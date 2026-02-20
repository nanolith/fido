/**
 * \file config/fido_config_command_create.c
 *
 * \brief Create a \ref fido_config_command instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

/**
 * \brief Create a \ref fido_config_command instance.
 *
 * \param cmd               Pointer to the command pointer to set to this
 *                          created instance on success.
 * \param binary            Real path to the binary.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_command_create(fido_config_command** cmd, const char* binary)
{
    int retval;
    fido_config_command* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_config_command_create, cmd, binary);

    /* allocate memory for this command. */
    tmp = (fido_config_command*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto error_exit;
    }

    /* set up command. */
    memset(tmp, 0, sizeof(*tmp));

    /* copy binary. */
    tmp->binary = strdup(binary);
    if (NULL == tmp->binary)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    /* success. */
    *cmd = tmp;
    retval = 0;
    goto done;

cleanup_tmp:
    fido_config_command_release(tmp);

error_exit:
    *cmd = NULL;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_command_create, retval, cmd, binary);

    return retval;
}
