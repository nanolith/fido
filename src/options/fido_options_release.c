/**
 * \file config/fido_options_release.c
 *
 * \brief Release an options instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/options.h>
#include <stdlib.h>

/**
 * \brief Release a \ref fido_options instance.
 *
 * \param opts          The options record to release.
 */
void fido_options_release(fido_options* opts)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_options_release, opts);

    /* free config file override if set. */
    if (NULL != opts->config_file_override)
    {
        free(opts->config_file_override);
    }

    /* free binary name if set. */
    if (NULL != opts->binary_name)
    {
        free(opts->binary_name);
    }

    /* free arguments if set. */
    if (NULL != opts->arguments)
    {
        for (size_t i = 0; i < opts->arguments_count; ++i)
        {
            if (NULL != opts->arguments[i])
            {
                free(opts->arguments[i]);
            }
        }

        free(opts->arguments);
    }

    /* free options instance. */
    free(opts);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_options_release, NULL);
}
