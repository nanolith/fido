/**
 * \file fido/options.h
 *
 * \brief Command-line option parsing.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/error_codes.h>
#include <stdbool.h>
#include <stddef.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Command-line options structure.
 */
typedef struct fido_options fido_options;
struct fido_options
{
    bool dry_run;
    char* binary_name;
    char** arguments;
    size_t arguments_count;
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
