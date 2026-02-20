/**
 * \file config/fido_config_add_variable.c
 *
 * \brief Release a \ref fido_config_add_variable instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Release a \ref fido_config_add_variable instance.
 *
 * \param var           The add variable instance to release.
 */
void fido_config_add_variable_release(fido_config_add_variable* var)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_config_add_variable_release, var);

    /* clean up name if set. */
    if (NULL != var->name)
    {
        free(var->name);
    }

    free(var);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_config_add_variable_release, var);
}
