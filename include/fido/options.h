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
#include <fido/function_contracts.h>
#include <fido/function_decl.h>
#include <fido/model_assert.h>
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

/******************************************************************************/
/* Start of model checking properties.                                        */
/******************************************************************************/

/**
 * \brief Valid options record property.
 *
 * \param opts          The options record to check.
 *
 * \returns true if the options record is valid.
 */
bool
property_fido_options_valid(
    const fido_options* opts);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create a fido options record from command-line arguments.
 *
 * \param opts          Pointer to the options record pointer to populate with
 *                      the created options record on success.
 * \param argc          The argument count.
 * \param argv          The argument vector.
 *
 * \returns 0 on success and non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_options_create(fido_options** opts, int argc, const char** argv);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_options_create, fido_options** opts, int argc, const char** argv)
        /* the options pointer is valid. */
        MODEL_CHECK_OBJECT_RW(opts, sizeof(*opts));
        /* the argument vector is valid. */
        MODEL_CHECK_OBJECT_READ(argv, argc * sizeof(const char*));
MODEL_CONTRACT_PRECONDITIONS_END(fido_options_create)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
