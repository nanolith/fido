/**
 * \file env/fido_env_vararray_release.c
 *
 * \brief Release a vararray instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/env.h>
#include <stdlib.h>

/**
 * \brief Release a variable array instance.
 *
 * \param varr          The instance to release.
 */
void fido_env_vararray_release(char** varr)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_env_vararray_release, varr);

    for (size_t i = 0; NULL != varr[i]; ++i)
    {
        free(varr[i]);
    }

    free(varr);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_env_vararray_release, varr);
}
