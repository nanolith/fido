/**
 * \file config/fido_config_command_argument_create.c
 *
 * \brief Create a \ref fido_config_command_argument instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

/**
 * \brief Create a \ref fido_command_argument instance.
 *
 * \param arg               Pointer to the argument pointer to set to this
 *                          created instance on success.
 * \param argument_type     The type of argument. \see \ref
 *                          fido_config_command_argument_type.
 * \param argument_match    The match expression for the argument.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_command_argument_create(
    fido_config_command_argument** arg, int argument_type,
    const char* argument_match)
{
    int retval;
    fido_config_command_argument* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_command_argument_create, arg, argument_type,
        argument_match);

    /* allocate memory for this argument. */
    tmp = (fido_config_command_argument*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto error_exit;
    }

    /* set up argument. */
    memset(tmp, 0, sizeof(*tmp));
    tmp->argument_type = argument_type;

    /* copy argument_match. */
    tmp->argument_match = strdup(argument_match);
    if (NULL == tmp->argument_match)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    /* success. */
    *arg = tmp;
    retval = 0;
    goto done;

cleanup_tmp:
    fido_config_command_argument_release(tmp);

error_exit:
    *arg = NULL;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_command_argument_create, retval, arg, argument_type,
        argument_match);

    return retval;
}
