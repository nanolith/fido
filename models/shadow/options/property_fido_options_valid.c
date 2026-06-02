/**
 * \file models/shadow/options/property_fido_options_valid.c
 *
 * \brief Model checking property to ensure that a fido options instance is
 * valid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/options.h>

/**
 * \brief Valid options record property.
 *
 * \param opts          The options record to check.
 *
 * \returns true if the options record is valid.
 */
bool
property_fido_options_valid(const fido_options* opts)
{
    MODEL_CHECK_OBJECT_READ(opts, sizeof(*opts));

    MODEL_ASSERT(NULL != opts->original_binary_name);
    MODEL_ASSERT(NULL != opts->binary_name);
    if (opts->arguments_count > 0)
    {
        MODEL_ASSERT(NULL != opts->arguments);
        MODEL_CHECK_OBJECT_READ(
            opts->arguments,
            opts->arguments_count * sizeof(const char*));
        size_t offset;
        MODEL_ASSUME(offset < opts->arguments_count);
        MODEL_ASSERT(NULL != opts->arguments[offset]);
    }
    else
    {
        MODEL_ASSERT(NULL == opts->arguments);
    }

    return true;
}
